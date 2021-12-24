#include <stdio.h>
#include "lexer.h"

int token;
int isFirstPrinting = 1;

typedef enum parsingStatus {
   ACCEPTED,
   REJECTED,
   INCOMPLETE
}parsingStatus;

parsingStatus status;


char* getTokenName(int tokenType){
    switch (tokenType){
        case IF:
            return "if";
        case THEN:
            return "then";
        case ELSE:
            return "else";
        case END:
            return "end";
        case BEGIN:
            return "begin";
        case PRINT:
            return "print";
        case SEMICOL:
            return ";";
        case EQ:
            return "=";
        case NUM:
            return "num";
        case ERROR:
            return "error";
    }
}

void printNewLine(){
    if(!isFirstPrinting) printf("\n");
    else isFirstPrinting = 0;
}

void printError(int readToken, char* expectedToken){
    printNewLine();
    printf("ERRO SINTATICO EM: %s ESPERADO: %s", getTokenName(readToken), expectedToken);
    status = REJECTED;
}

void ignoreInvalidStringRemainingTokens(){
    while(token != NEW_LINE && token != EOF_TOKEN)
        token = getNextToken();
}

void advance() {
    token=getNextToken();
}

void eat(int t) {
    if (token==NEW_LINE || token==EOF_TOKEN){
        if(status == ACCEPTED) status = INCOMPLETE;
        return;
    }
    else if (token==t) advance(); 
    else{
        printError(token, getTokenName(t));
        ignoreInvalidStringRemainingTokens(); 
    }
}

parsingStatus S();

void L(){
    if (token==NEW_LINE || token==EOF_TOKEN){
        if(status == ACCEPTED) status = INCOMPLETE;
        return;
    }
    switch(token) {
        case END: eat(END); break;
        case SEMICOL: eat(SEMICOL); S(); L(); break;
        default: 
            printError(token, "end, ;"); 
            ignoreInvalidStringRemainingTokens();
    }
}

void E(){
    if (token==NEW_LINE || token==EOF_TOKEN){
        if(status == ACCEPTED) status = INCOMPLETE;
        return;
    }
    eat(NUM); 
    eat(EQ); 
    eat(NUM); 
}


parsingStatus S(){
    if (token==NEW_LINE || token==EOF_TOKEN) {
        if(status == ACCEPTED) status = INCOMPLETE;
        return status;
    }
    switch(token) {
        case IF: eat(IF); E(); eat(THEN); S(); eat(ELSE); S(); break;
        case BEGIN: eat(BEGIN); S(); L(); break;
        case PRINT: eat(PRINT); E(); break;
        default:
            printError(token, "if, begin, print");
            ignoreInvalidStringRemainingTokens();
    }
    return status;
}


int parse(){
    token = getNextToken();
    
    while(token != EOF_TOKEN){ //if the next token exists, we try to parse another string...
        status = ACCEPTED;
        status = S();
        if(status == ACCEPTED){
            printNewLine();
            printf("CADEIA ACEITA");
        }else if (status == INCOMPLETE){
            printNewLine();
            printf("ERRO SINTATICO: CADEIA INCOMPLETA");
        }

        token = getNextToken(); //ignoring a possible '\n' token.
    }
}