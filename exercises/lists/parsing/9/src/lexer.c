#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

#define INITIAL_STATE 1
#define ALPHABET_LENGTH 29

int edges[][ALPHABET_LENGTH] = {
                  /*input characters
                  +   -   0   1   2   3   4   5   6   7   8   9   =   ;   d   e   f   g   h   i   t   n   l   s   b   p   r  \n   O
    /*state 0*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    /*state 1*/  {18,18, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 26, 25,  0,  6,  0,  0,  0,  2,  3,  0,  0,  0, 10, 14,  0, 28,  0},
    /*state 2*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 19,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    /*state 3*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    /*state 4*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    /*state 5*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 20,  0,  0,  0,  0,  0,  0,  0},
    /*state 6*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9,  7,  0,  0,  0,  0,  0,  0},
    /*state 7*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  0,  0,  0,  0,  0},
    /*state 8*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 21,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    /*state 9*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 22,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    /*state 10*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    /*state 11*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 12,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    /*state 12*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 13,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    /*state 13*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 23,  0,  0,  0,  0,  0,  0,  0},
    /*state 14*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15,  0,  0},
    /*state 15*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    /*state 16*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 17,  0,  0,  0,  0,  0,  0,  0},
    /*state 17*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 24,  0,  0,  0,  0,  0,  0,  0,  0},
    /*state 18*/ {0,  0, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    /*state 19*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    /*state 20*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    /*state 21*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    /*state 22*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    /*state 23*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    /*state 24*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    /*state 25*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    /*state 26*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    /*state 27*/ {0,  0, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    /*state 28*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},

    /*obs: O stands for other*/
};

int isFinalState(int state){
    if(state > 18 && state < 29) return 1;
    else return 0;  
}

int getCharacterColumnIndex(char character){ 
    //+   -   0   1   2   3   4   5   6   7   8   9   =   ;   d   e   f   g   h   i   t   n   l   s   b   p   r   \n   O
    if(character == '+') return 0;
    else if(character == '-') return 1;
    else if(character >= '0' && character <= '9') return (1 + (character - 47));
    else if(character == '=') return 12;
    else if(character == ';') return 13;
    else if(character >= 'd' && character <= 'i') return (13 + (character - 99));  
    else if(character == 't') return 20;
    else if(character == 'n') return 21;
    else if(character == 'l') return 22;
    else if(character == 's') return 23;
    else if(character == 'b') return 24;
    else if(character == 'p') return 25;
    else if(character == 'r') return 26;
    else if(character == '\n') return 27;
    else return 28; //other
}

int getNextState(int currentState, char character){
    int index = getCharacterColumnIndex(character);
    return edges[currentState][index];
}

tokenType getFinalStateTokenType(int finalState){
    if (finalState == 0) return ERROR;  
    else return finalState - 19;
}

tokenType getNextToken(){

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
            return getFinalStateTokenType(lastFinalState);
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

            return getFinalStateTokenType(lastFinalState);

        }
        else if(isFinalState(currentState)){ //the automaton is now recognizing a longer substring (lexeme).

            lastFinalState = currentState;
            acceptingCursor = readingCursor;
        }
    }
}