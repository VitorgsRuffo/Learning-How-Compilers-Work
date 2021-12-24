#ifndef LEXER_H
#define LEXER_H

typedef enum tokenType {
    DOLLAR,
    PLUS,
    TIMES,
    L_PAREN,
    R_PAREN,
    ID,
    NEW_LINE,
    EOF_TOKEN    // returned when end of input file is reached.
}tokenType;

//returns a tokenType value corresponding to the next token code.
//when next token is invalid the character ascii code representing it is returned.
int getNextToken();

#endif