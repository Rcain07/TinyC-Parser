# ifndef TOKENS_H
# define TOKENS_H


/*
COPYRIGHT 2019, Ryan Cain, All Rights Reserved.
This code is made by me for my academic use in the class COEN 259 with a few expecptions of code given from
a textbook/teacher.
*/

/* 
This enum is useful for tokenizing the input stream that we can play around with later.
For convience, most of the operators are assigned to their askii values while everything else begins at 256 and increments.
*/
enum {
    ASSIGN = '=', LTN = '<', GTN = '>', PLUS = '+', MINUS = '-',
    STAR = '*', DIV = '/', REM = '%', ADDR = '&', NOT = '!', DOT = '.',
    LPAREN = '(', RPAREN = ')', LBRACK = '[', RBRACK = ']',
    LBRACE = '{', RBRACE = '}', SEMI = ';', COLON = ':', COMMA = ',',

    AUTO = 256, BREAK, CASE, CHAR, CONST, CONTINUE, DEFAULT, DO, DOUBLE,
    ELSE, ENUM, EXTERN, FLOAT, FOR, GOTO, IF, INT, LONG, REGISTER,
    RETURN, SHORT, SIGNED, SIZEOF, STATIC, STRUCT, SWITCH, TYPEDEF,
    UNION, UNSIGNED, VOID, VOLATILE, WHILE,

    OR, AND, EQL, NEQ, LEQ, GEQ, INC, DEC,
    ID, NUM, STRING, CHARLIT, DONE = 0, ERROR = -1
};

# endif /* TOKENS_H */