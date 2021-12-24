#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_STATE 1
#define INPUT_LINE_SIZE 1026 //one line can have until 1024 chars besides the '\n' and '\0' last characters.

int isFinalState(int state){
    if((state  >= 2 && state <= 5) || state == 8) return 1;
    else return 0;  
}

int getNextState(int currentState, char input){

    if(currentState == 0 || currentState == 3 || currentState == 4 || input == '\n' || input == '\0') return 0;
    
    else if (currentState == 1){ //initial state

        if(input == '+') return 3;
        if(input == '-') return 4;
        if(input >= '0' && input <= '9') return 5;
        if(input >= 'a' && input <= 'z') return 2;

        return -1;

    }else if (currentState == 2){
        
        if(input == '+' || input ==  '-') return 0;
        if((input >= '0' && input <= '9') || (input >= 'a' && input <= 'z')) return 2;

        return 0;

    }else if (currentState == 5){
        
        if(input == '+' || input ==  '-') return 0;
        if(input >= '0' && input <= '9')  return 5;
        if(input == 'e') return 6;
        if(input >= 'a' && input <= 'z') return 0;

        return 0;

    }else if (currentState == 6){
        
        if(input == '+' || input ==  '-') return 7;
        if(input >= '0' && input <= '9')  return 8;
        if(input >= 'a' && input <= 'z') return 0;

        return 0;

    }else if (currentState == 7 || currentState == 8){
        if(input == '+' || input ==  '-') return 0;
        if(input >= '0' && input <= '9')  return 8;
        if(input >= 'a' && input <= 'z') return 0;

        return 0;

    }else return -1;

}


void processLexeme(char* address, int length){
    if(length == 0) return;
    char temp = address[length];
    address[length] = '\0';
    printf("%s\n", address);
    address[length] = temp;
}


int main(void){
    
    int edges[][39] = {/*input characters
                     +  -  0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z \n*/    
        /*state 0*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        /*state 1*/ {3, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0},
        /*state 2*/ {0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0},
        /*state 3*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        /*state 4*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        /*state 5*/ {0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        /*state 6*/ {7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        /*state 7*/ {0, 0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        /*state 8*/ {0, 0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
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
            currentState = getNextState(currentState, currentChar);
            
            if(currentState == -1){ //invalid character/state
                printf("ERROR\n");
                baseAddress += 1;
                acceptingCursor = 0;
                readingCursor = 0;
                lastFinalState = 0;
                currentState = INITIAL_STATE;
                continue;
            }
            else if(currentState == 0){ //the automaton transition function is not defined for the current state-input pair. So it may have recognized some token.
                
                if(*baseAddress == '\n' || *baseAddress == '\0') break; //finished processing line

                processLexeme(baseAddress, acceptingCursor);
                baseAddress += acceptingCursor;
                acceptingCursor = 0;
                readingCursor = 0;
                lastFinalState = 0;
                currentState = INITIAL_STATE;

            }
            else if(isFinalState(currentState)){ //the automaton is now recognizing a new substring (lexeme).

                lastFinalState = currentState;
                acceptingCursor = readingCursor;
            }
        }

    }

    return 0;
}