%{

#include <stdio.h>
#include <string.h>
#include <hashtable.h>
#include <record.h>

extern int yylex();
extern char* yytext;
void yyerror(char *s);
HashTable ht;
char currentType[10];
int errorFlag = 0;

int line = 1;
int isFirstTokenPrinted = 0;
void printMessage(int line, char* message);
void saveSymbol(char* symbol);

%}


%union{
    char string[1000];
}

%token DOLLAR
%token INT
%token FLOAT
%token CHAR
%token COMMA
%token ID
%token EOL
%token _EOF

%start Sprime

%type <string> ID


%%

Sprime: S EOL  {if(!errorFlag) printMessage(line, "All Identifiers on Hash."); line++; return 0;}
      | S _EOF {if(!errorFlag) printMessage(line, "All Identifiers on Hash."); return 1;}
      | _EOF   {return 1;}
;

S: D Dprime DOLLAR {}
;

Dprime: D Dprime {}
      | {}
;

D: T I {}
;

T: INT   {strcpy(currentType, "int");}
 | FLOAT {strcpy(currentType, "float");}
 | CHAR  {strcpy(currentType, "char");}
;

I: ID         {saveSymbol($1);}
 | I COMMA ID {saveSymbol($3);}
;


%%

void saveSymbol(char* symbol){
    Info info;
    info = getHashTableInfo(ht, symbol);
    
    if(info != NULL){ //erro: id ja foi inserido na tabela de simbolos... 

        char message[50];
        if(strcmp(currentType, getRecordType(info)) == 0) //identificador ja declarado...
            sprintf(message, "identifier '%s' already declared", symbol); 

        else//redefinicao de indentificador...
            sprintf(message, "redefinition of identifier '%s'", symbol); 

        printMessage(line, message); 
        errorFlag = 1;
        return;
    }
    
    char* s = (char*) malloc((strlen(symbol)+1)*sizeof(char));
    sprintf(s, "%s", symbol);
    Record rec = newRecord(s, currentType);
    insertHashTable(&ht, rec); //adiciona novo identificador na tabela de simbolos...
    return;
}

void printMessage(int line, char* message){
    if(!isFirstTokenPrinted)
        isFirstTokenPrinted = 1;
    else
        printf("\n");
    printf("%d: %s", line, message);
}


void yyerror(char *s){
    return;
}

int main(int argc, char **argv)
{
    ht = createHashTable(97, getRecordId);
    while(!yyparse()){
        freeHashTable(ht, freeRecord);
        ht = createHashTable(97, getRecordId);
        errorFlag = 0;
    };
    freeHashTable(ht, freeRecord);
}
