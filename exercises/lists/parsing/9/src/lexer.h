#ifndef LEXER_H
#define LEXER_H

typedef enum tokenType {
    IF,
    THEN,
    ELSE,
    END,
    BEGIN,
    PRINT,
    SEMICOL,
    EQ,
    NUM,
    NEW_LINE,
    ERROR,       // returned when next token is invalid.
    EOF_TOKEN    // returned when end of input file is reached.
}tokenType;

tokenType getNextToken();

#endif