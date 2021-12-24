#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_STATE 1
#define INPUT_LINE_SIZE 4098 //one line can have until 4096 chars besides the '\n' and '\0' last characters.

int isFinalState(int state){
    if((state  >= 13 && state <= 19) || state == 3 || state == 6 || state == 8 || state == 10 || state == 22) return 1;
    else return 0;  
}

int getCharColumnIndex(char character){ 
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

int getNextState(int currentState, char character, int edges[][21]){
    int index = getCharColumnIndex(character);
    return edges[currentState][index];
}

void processLexeme(char* address, int length, int finalState, int* firstToken){
    char temp = address[length];
    address[length] = '\0';

    if(*firstToken)
        *firstToken = 0;
    else
        printf("\n");
    

    if(finalState == 3) 
        printf("ELE");
    else if(finalState == 6)
        printf("ELA");
    else if(finalState == 8)
        printf("DELE");
    else if(finalState == 10)
        printf("DELA");
    else if(finalState == 13)
        printf("GATO");
    else if(finalState == 15)
        printf("GATOS");
    else if(finalState == 14)
        printf("CARRO");
    else if(finalState == 16)
        printf("CARROS");
    else if(finalState == 17)
        printf("MAIS");
    else if(finalState == 18)
        printf("MENOS");
    else if(finalState == 19)
        printf("INTEIRO %s", address);
    else if(finalState == 22)
        printf("REAL %s", address);

    address[length] = temp;
}


int main(void){
    
    int edges[][21] = {/*input characters
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

    char inputLine[INPUT_LINE_SIZE];

    int firstToken = 1;

    while(fgets(inputLine, INPUT_LINE_SIZE, stdin) != NULL){
        
        int lastFinalState = 0;
        int currentState = INITIAL_STATE;
        
        int acceptingCursor = 0;
        int readingCursor = 0;

        char* baseAddress = inputLine;

        while(1){         

            //reading next character:
            char currentChar = baseAddress[readingCursor];
            readingCursor++;

            //changing state based on read character:
            currentState = getNextState(currentState, currentChar, edges);
            
            if(currentState == 0){ //the automaton transition function is not defined for the current state-input pair. So it may have fished recognizing some token instance (lexeme).
                
                if(*baseAddress == '\n' || *baseAddress == '\0') break; //finished processing line

                if(acceptingCursor != 0){ //the automaton recognized a lexeme starting at (baseAddress) and ending at ((baseAddress + acceptingCursor) - 1).

                    processLexeme(baseAddress, acceptingCursor, lastFinalState, &firstToken);
                    baseAddress += acceptingCursor;
                    acceptingCursor = 0;
                }
                else{ //the automaton could not recognize a lexeme starting at "baseAddress".
                    if(*baseAddress != ' '){ //we're ignoring white spaces.
                        if(firstToken)
                            firstToken = 0;
                        else
                            printf("\n");  
                        printf("ERRO");
                    }
                    baseAddress += 1;
                }
                readingCursor = 0;
                lastFinalState = 0;
                currentState = INITIAL_STATE;

            }
            else if(isFinalState(currentState)){ //the automaton is now recognizing a longer substring (lexeme).

                lastFinalState = currentState;
                acceptingCursor = readingCursor;
            }
        }

    }

    return 0;
}
