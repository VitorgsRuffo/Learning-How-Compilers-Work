#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_STATE 1
#define INPUT_LINE_SIZE 1026 //one line can have until 1024 chars besides the '\n' and '\0' last characters.

int isFinalState(int state){
    if((state  >= 2 && state <= 9) || (state >= 11 && state <= 13)) return 1;
    else return 0;  
}

int getCharColumnIndex(char character){
    //B  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z  0  1  2  3  4  5  6  7  8  9  .  - \n  O*/    
    if(character == ' ') return 0;
    else if(character >= 'a' && character <= 'z') return (character - 96);
    else if(character >= '0' && character <= '9') return (26 + (character - 47));
    else if(character == '.') return 37;
    else if(character == '-') return 38;
    else if(character == '\n') return 39;
    else return 40; //other
}

int getNextState(int currentState, char character, int edges[][41]){
    int index = getCharColumnIndex(character);
    return edges[currentState][index];
}

void processLexeme(char* address, int length, int finalState){
    if(length == 0) return;
    char temp = address[length];
    address[length] = '\0';

    if(finalState == 2 || finalState == 4) 
        printf("%s ID\n", address);
    else if(finalState == 3)
        printf("IF\n");
    else if(finalState == 12)
        printf("white space\n");
    else if(finalState == 13 || finalState == 9 || finalState == 5)
        printf("%s error\n", address);
    else if(finalState == 6 || finalState == 8)
        printf("%s REAL\n", address);
    else if(finalState == 7)
        printf("%s NUM\n", address);
    else if(finalState == 11){
        address[length-1] = '\0';
        printf("%s comment\n", address);
        address[length-1] = '\n';
    }

    address[length] = temp;
}


int main(void){
    
    int edges[][41] = {/*input characters
                      B   a   b   c   d   e   f   g   h   i   j   k   l   m   n   o   p   q   r   s   t   u   v   w   x   y   z   0   1   2   3   4   5   6   7   8   9   .   -  \n   O*/    
        /*state 0*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 1*/  {12, 4,  4,  4,  4,  4,  4,  4,  4,  2,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  5,  9, 13, 13},
        /*state 2*/  {0,  4,  4,  4,  4,  4,  3,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  0,  0,  0,  0},
        /*state 3*/  {0,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  0,  0,  0,  0},
        /*state 4*/  {0,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  0,  0,  0,  0},
        /*state 5*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  0,  0,  0,  0},
        /*state 6*/  {0,  0,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  0,  0,  0,  0},
        /*state 7*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  8,  0,  0,  0},
        /*state 8*/  {0,  0,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  0,  0,  0,  0},
        /*state 9*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10,  0,  0},
        /*state 10*/ {0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 11,  0},
        /*state 11*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 12*/ {12, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 13*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},

        /*obs: B stands for blank and O stands for other*/
    };

    char inputLine[INPUT_LINE_SIZE];

    //FILE* in = fopen("input.txt", "r");

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

                processLexeme(baseAddress, acceptingCursor, lastFinalState);
                baseAddress += acceptingCursor;
                acceptingCursor = 0;
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