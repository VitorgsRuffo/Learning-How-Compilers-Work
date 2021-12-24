#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

#define INITIAL_STATE 1
#define ALPHABET_LENGTH 43

int edges[][ALPHABET_LENGTH] = {
                  /*input characters
                  $   +   *   (   )   a   b   c   d   e   f   g   h   i   j   k   l   m   n   o   p   q   r   s   t   u   v   w   x   y   z   0   1   2   3   4   5   6   7   8   9  \n   O
    /*state 0*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    /*state 1*/  {2,  3,  4,  5,  6,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  0},
    /*state 2*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    /*state 3*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    /*state 4*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    /*state 5*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    /*state 6*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    /*state 7*/  {0,  0,  0,  0,  0,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  0,  0},
    /*state 8*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},

    /*obs: O stands for other*/
};

int isFinalState(int state){
    if(state > 1) return 1;
    else return 0;  
}

int getCharacterColumnIndex(char character){ 
    //$   +   *   (   )   a   b   c   d   e   f   g   h   i   j   k   l   m   n   o   p   q   r   s   t   u   v   w   x   y   z   0   1   2   3   4   5   6   7   8   9  \n   O
    if(character == '$') return 0;
    else if(character == '+') return 1;
    else if(character == '*') return 2;
    else if(character == '(') return 3;
    else if(character == ')') return 4;
    else if(character >= 'a' && character <= 'z') return (4 + (character - 96));
    else if(character >= '0' && character <= '9') return (30 + (character - 47));  
    else if(character == '\n') return 41;
    else return 42; //other
}

int getNextState(int currentState, char character){
    int index = getCharacterColumnIndex(character);
    return edges[currentState][index];
}

int getFinalStateTokenType(int finalState, char currentChar){
    if (finalState == 0) return currentChar;  
    else return finalState - 2;
}

int getNextToken(){

    int lastFinalState = 0;
    int currentState = INITIAL_STATE;
    
    int acceptingCursor = 0;
    int readingCursor = 0;
    
    char currentChar;

    while(1){ 

        if(fread(&currentChar, 1, 1, stdin) != 1){ //EOF reached. Checking if some token was recognized.
            if(readingCursor == 0) //there are no tokens left to be recognized
                return EOF_TOKEN;

            //repositioning the file position indicator to be just after the recognized token (or, in case no token was recognized, one position forward).
            int offset = readingCursor - acceptingCursor;
            if(acceptingCursor == 0) //the automaton could not recognize a lexeme.
                offset--;
            fseek(stdin, -offset, SEEK_CUR);

            //return token type.
            return getFinalStateTokenType(lastFinalState, currentChar);
        }
        
        readingCursor++;

        //changing state based on read character:
        currentState = getNextState(currentState, currentChar);
        
        if(currentState == 0){ //the automaton transition function is not defined for the current state-input pair.
            
            //repositioning the file position indicator to be just after the recognized token (or, in case no token was recognized, one position forward).
            int offset = readingCursor - acceptingCursor;

            if(acceptingCursor == 0){//the automaton could not recognize a token.
                
                if(readingCursor == 1 && (currentChar == ' ')) //only one character was read: the first state cannot transition to another state by consuming it. If that character is ' ' (or any other we want) we'll ignore it.
                    return getNextToken(); //so, we ignore those characters and try again to get the next token.
                
                else  //otherwise, we continue with file position indicator repositioning.
                    offset--;
            } 
            fseek(stdin, -offset, SEEK_CUR);

            return getFinalStateTokenType(lastFinalState, currentChar);

        }
        else if(isFinalState(currentState)){ //the automaton is now recognizing a longer substring (lexeme).

            lastFinalState = currentState;
            acceptingCursor = readingCursor;
        }
    }
}