#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "stack.h"

typedef void (*Function)(void); 
void E();
void E_quote();
void T();
void T_quote();
void F();
void S();

Stack St;
int token;
int isFirstPrinting = 1;

typedef enum parsingStatus {
   ACCEPTED,
   REJECTED
}parsingStatus;

parsingStatus status;


void cleanStack(){
    while(stackTop(St) != NULL){
        Data top = stackPop(St);
        if(top != E && top != E_quote && top != T && top != T_quote && top != F && top != S)
            free(top);
    }
}

char* getTokenName(int tokenType){
    switch (tokenType){
        case DOLLAR:
            return " $ ";
        case PLUS:
            return " + ";
        case TIMES:
            return " * ";
        case L_PAREN:
            return " ( ";
        case R_PAREN:
            return " ) ";
        case ID:
            return " id ";
        default:
            return " ";
    }
}

void printNewLine(){
    if(!isFirstPrinting) printf("\n");
    else isFirstPrinting = 0;
}

void printLexicalError(char character){
    printNewLine();
    printf("ERRO LEXICO: %c", character);
    status = REJECTED;
}

void printSyntaxError(int readToken, char* expectedToken){
    printNewLine();
    printf("ERRO SINTATICO EM:%sESPERADO: %s", getTokenName(readToken), expectedToken);
    status = REJECTED;
}

void ignoreInvalidStringRemainingTokens(){
    while(token != NEW_LINE && token != EOF_TOKEN)
        token = getNextToken();
}

void advance() {
    token=getNextToken();
}

int getProductionByNonTerminalAndTerminalPair(char nonT, int T){
    switch(nonT){
        case 'S':
        case 'E':
        case 'T':
            if (T == ID || T == L_PAREN) return 0;
            return -1;
        case 'e':
            if (T == PLUS) return 0;
            if (T == R_PAREN || T == DOLLAR) return 1;
            return -1;
        case 't':
            if (T == TIMES) return 0;
            if (T == PLUS || T == R_PAREN || T == DOLLAR) return 1;
            return -1;
        case 'F':
            if(T == ID) return 0; 
            if(T == L_PAREN) return 1;
            return -1;
    }
}

int match(){
    int* top = (int*) stackTop(St);
    while(*top == token){
        stackPop(St);
        free(top);
        advance();
        top = (int*) stackTop(St);
        if(top == NULL) return 1;
    }
    if (*top >= DOLLAR && *top <= ID) //stack top has a token, and it is not equal to the current token. So, we must reject current string.
        return 0;
    return 1;
}

void derive(int matchWasSuccessful){
    if(matchWasSuccessful){ //derive non-Terminal at the top of the stack.
        Function top = stackTop(St);
        if(top != NULL)
            (*top)();

    }else{ //stack top has a token, and, it is not equal to the current token. So, we must reject current string.
        int* top = (int*) stackTop(St);
        char* tokenName = getTokenName(*top);
        int tokenNameLen = strlen(tokenName);
        char tName[10];
        sprintf(tName, "%s", &tokenName[1]);
        tName[tokenNameLen-2] = '\0';
        printSyntaxError(token, tName);
        ignoreInvalidStringRemainingTokens();
    }
}

void stackPushToken(int token) {
    int* t = (int*) malloc(sizeof(int));
    *t = token;
    stackPush(St, t);
}


void S(){
    //printf("S.\n");
    if (token > EOF_TOKEN){ //next token is invalid. We stop parsing the current string, print an error and go to the next one.
        printLexicalError(token);
        ignoreInvalidStringRemainingTokens();
        return;
    } 
    if (token == NEW_LINE || token == EOF_TOKEN){ //we have reached current string's end without emptying the stack (that means it is incomplete). We print a syntax error and go to the next one.
        printSyntaxError(-1, "id, (");
        return;
    }
    int action = getProductionByNonTerminalAndTerminalPair('S', token);
    switch(action) {
        case 0:
            stackPop(St);
            stackPushToken(DOLLAR);            
            stackPush(St, E);
            break;
        default:
            printSyntaxError(token, "id, (");
            ignoreInvalidStringRemainingTokens();
            return;
    }
    int matchWasSuccessful = match();
    derive(matchWasSuccessful);
}

void E(){
    //printf("E.\n");
    if (token > EOF_TOKEN){ //next token is invalid. We stop parsing the current string, print an error and go to the next one.
        printLexicalError(token);
        ignoreInvalidStringRemainingTokens();
        return;
    }
    if (token == NEW_LINE || token == EOF_TOKEN){ //we have reached current string's end without emptying the stack (that means it is incomplete). We print a syntax error and go to the next one.
        printSyntaxError(-1, "id, (");
        return;
    }
    int action = getProductionByNonTerminalAndTerminalPair('E', token);
    switch(action) {
        case 0:
            stackPop(St);
            stackPush(St, E_quote);
            stackPush(St, T);
            break;
        default:
            printSyntaxError(token, "id, (");
            ignoreInvalidStringRemainingTokens();
            return;
    }
    int matchWasSuccessful = match();
    derive(matchWasSuccessful);
}

void E_quote(){
    //printf("Eq.\n");
    if (token > EOF_TOKEN){ //next token is invalid. We stop parsing the current string, print an error and go to the next one.
        printLexicalError(token);
        ignoreInvalidStringRemainingTokens();
        return;
    }
    if (token == NEW_LINE || token == EOF_TOKEN){ //we have reached current string's end without emptying the stack (that means it is incomplete). We print a syntax error and go to the next one.
        printSyntaxError(-1, "+, ), $");
        return;
    }
    int action = getProductionByNonTerminalAndTerminalPair('e', token);
    switch(action) {
        case 0:
            stackPop(St);
            stackPush(St, E_quote);
            stackPush(St, T);
            stackPushToken(PLUS);
            break;
        case 1:
            stackPop(St);
            break;
        default:
            printSyntaxError(token, "+, ), $");
            ignoreInvalidStringRemainingTokens();
            return;
    }
    int matchWasSuccessful = match();
    derive(matchWasSuccessful);
}

void T(){
    //printf("T.\n");
    if (token > EOF_TOKEN){ //next token is invalid. We stop parsing the current string, print an error and go to the next one.
        printLexicalError(token);
        ignoreInvalidStringRemainingTokens();
        return;
    }
    if (token == NEW_LINE || token == EOF_TOKEN){ //we have reached current string's end without emptying the stack (that means it is incomplete). We print a syntax error and go to the next one.
        printSyntaxError(-1, "id, (");
        return;
    }
    int action = getProductionByNonTerminalAndTerminalPair('T', token);
    switch(action) {
        case 0:
            stackPop(St);
            stackPush(St, T_quote);
            stackPush(St, F);
            break;
        default:
            printSyntaxError(token, "id, (");
            ignoreInvalidStringRemainingTokens();
            return;
    }
    int matchWasSuccessful = match();
    derive(matchWasSuccessful);
}

void T_quote(){
    //printf("Tq.\n");
    if (token > EOF_TOKEN){ //next token is invalid. We stop parsing the current string, print an error and go to the next one.
        printLexicalError(token);
        ignoreInvalidStringRemainingTokens();
        return;
    }
    if (token == NEW_LINE || token == EOF_TOKEN){ //we have reached current string's end without emptying the stack (that means it is incomplete). We print a syntax error and go to the next one.
        printSyntaxError(-1, "+, *, ), $");
        return;
    }
    int action = getProductionByNonTerminalAndTerminalPair('t', token);
    switch(action) {
        case 0:
            stackPop(St);
            stackPush(St, T_quote);
            stackPush(St, F);
            stackPushToken(TIMES);
            break;
        case 1:
            stackPop(St);
            break;
        default:
            printSyntaxError(token, "+, *, ), $");
            ignoreInvalidStringRemainingTokens();
            return;
    }
    int matchWasSuccessful = match();
    derive(matchWasSuccessful);
}

void F(){
    //printf("F.\n");
    if (token > EOF_TOKEN){ //next token is invalid. We stop parsing the current string, print an error and go to the next one.
        printLexicalError(token);
        ignoreInvalidStringRemainingTokens();
        return;
    }
    if (token == NEW_LINE || token == EOF_TOKEN){ //we have reached current string's end without emptying the stack (that means it is incomplete). We print a syntax error and go to the next one.
        printSyntaxError(-1, "id, (");
        return;
    }
    int action = getProductionByNonTerminalAndTerminalPair('F', token);
    switch(action) {
        case 0:
            stackPop(St);
            stackPushToken(ID);
            break;
        case 1:
            stackPop(St);
            stackPushToken(R_PAREN);
            stackPush(St, E);
            stackPushToken(L_PAREN);
            break;
        default:
            printSyntaxError(token, "id, (");
            ignoreInvalidStringRemainingTokens();
            return;
    }
    int matchWasSuccessful = match();
    derive(matchWasSuccessful);
}


int parse(){
    St = newStack();
    token = getNextToken();
    
    while(token != EOF_TOKEN){ //if the next token exists, we try to parse another string...
        status = ACCEPTED;
        stackPush(St, S);
        S();

        if(token == NEW_LINE || token == EOF_TOKEN) //if this evaluates to true it means that the string has already been accepted or rejected...            
            token = getNextToken(); //ignoring a possible '\n' token before next string parsing.
        
        else{ // otherwise, it means that we're uncertain if the string will be accepted, despite its current ACCEPTED state... A substring was already accepted but \n was not reached. So we need to check remaining characters to find the answer to our doubt: if there is at least one invalid token the string will be rejected, else it will be accepted without considering that remaining substring syntax.
            while(token != NEW_LINE && token != EOF_TOKEN){
                if(token > EOF_TOKEN){
                    printLexicalError(token);
                    ignoreInvalidStringRemainingTokens();
                    token = getNextToken(); //ignoring a possible '\n' token before next string parsing.
                    break;
                }
                token = getNextToken();
            }
        }

        if(status == ACCEPTED){
            printNewLine();
            printf("CADEIA ACEITA");
        }

        cleanStack(); //cleaning stack before next string parsing.
    }

    freeStack(St, NULL);
}