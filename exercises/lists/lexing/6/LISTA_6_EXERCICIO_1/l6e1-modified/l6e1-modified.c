#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_STATE 1
#define ALPHABET_LENGTH 21

typedef enum tokenType {
    ELE, 
    ELA, 
    DELE, 
    DELA, 
    GATO, 
    GATOS, 
    CARRO,
    CARROS,
    MAIS,
    MENOS,
    INTEIRO,
    REAL,
    ERRO
}tokenType; 

int isFinalState(int state){
    if((state  >= 13 && state <= 19) || state == 3 || state == 6 || state == 8 || state == 10 || state == 22) return 1;
    else return 0;  
}

int getCharacterColumnIndex(char character){ 
    // +   -   0   1   2   3   4   5   6   7   8   9   a   c   e   h   i   r   s   t
    if(character == '+') return 0;
    else if(character == '-') return 1;
    else if(character >= '0' && character <= '9') return (1 + (character - 47));
    else if(character == 'a') return 12;
    else if(character == 'c') return 13;
    else if(character == 'e') return 14;
    else if(character == 'h') return 15;
    else if(character == 'i') return 16;
    else if(character == 'r') return 17;
    else if(character == 's') return 18;
    else if(character == 't') return 19;
    else return 20; //other
}

int getNextState(int currentState, char character, int edges[][ALPHABET_LENGTH]){
    int index = getCharacterColumnIndex(character);
    return edges[currentState][index];
}

int getFinalStateTokenType(int finalState){
    if (finalState == 0)
        return ERRO;
    else if(finalState == 3) 
        return ELE;
    else if(finalState == 6)
        return ELA;
    else if(finalState == 8)
        return DELE;
    else if(finalState == 10)
        return DELA;
    else if(finalState == 13)
        return GATO;
    else if(finalState == 15)
        return GATOS;
    else if(finalState == 14)
        return CARRO;
    else if(finalState == 16)
        return CARROS;
    else if(finalState == 17)
        return MAIS;
    else if(finalState == 18)
        return MENOS;
    else if(finalState == 19)
        return INTEIRO;
    else if(finalState == 22)
        return REAL;

}

int getNextToken(int edges[][ALPHABET_LENGTH]);

int main(void){
    
    int edges[][ALPHABET_LENGTH] = {/*input characters
                      +   -   0   1   2   3   4   5   6   7   8   9   a   c   e   h   i   r   s   t   O
        /*state 0*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 1*/  {17,18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,  0, 11,  0,  2,  0,  0,  4,  0,  0},
        /*state 2*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  0,  7,  0,  0,  0,  0},
        /*state 3*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9,  0,  0,  0},
        /*state 4*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  5,  0,  0,  0,  0,  0},
        /*state 5*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6,  0,  0,  0,  0,  0,  0},
        /*state 6*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 7*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  0,  0},
        /*state 8*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 9*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10,  0,  0},
        /*state 10*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 11*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 12,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 12*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 14,  0, 13,  0},
        /*state 13*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15,  0,  0},
        /*state 14*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16,  0,  0},
        /*state 15*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 16*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 17*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 18*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 19*/ {0,  0, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,  0,  0, 20,  0,  0,  0,  0,  0,  0},
        /*state 20*/ {21,21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 21*/ {0,  0, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 22*/ {0,  0, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,  0,  0,  0,  0,  0,  0,  0,  0,  0},

        /*obs: O stands for other*/
    };

    for(int i = 0; i<100; i++){
        int token =  getNextToken(edges);
        if(token < 0) break;
        printf("token id: %d.\n\n", token);
    }

    return 0;
}

int getNextToken(int edges[][ALPHABET_LENGTH]){

    int lastFinalState = 0;
    int currentState = INITIAL_STATE;
    
    int acceptingCursor = 0;
    int readingCursor = 0;
    
    char currentChar;

    while(1){ 

        if(fread(&currentChar, 1, 1, stdin) != 1){ //EOF reached. Checking if some token was recognized.
            if(readingCursor == 0) //there are no tokens left to be recognized
                return -1;

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
        currentState = getNextState(currentState, currentChar, edges);
        
        if(currentState == 0){ //the automaton transition function is not defined for the current state-input pair.
            
            //repositioning the file position indicator to be just after the recognized token (or, in case no token was recognized, one position forward).
            int offset = readingCursor - acceptingCursor;
            if(acceptingCursor == 0) //the automaton could not recognize a lexeme.
                offset--;
            fseek(stdin, -offset, SEEK_CUR);

            return getFinalStateTokenType(lastFinalState);

        }
        else if(isFinalState(currentState)){ //the automaton is now recognizing a longer substring (lexeme).

            lastFinalState = currentState;
            acceptingCursor = readingCursor;
        }
    }
}