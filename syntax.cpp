#include <iostream>
#include "lexer.h"
#include <string>
#include "TOKENS.h"

/*
COPYRIGHT 2019, Ryan Cain, All Rights Reserved.
This code is made by me for my academic use in the class COEN 259 with a few expecptions of code given from
a textbook/teacher.
*/

using namespace std;

int word;
string lexeme;

void statements();
void expression();

/*
Syntax file that handles checking the input file against the grammar of the language.
In the case of Tiny C, most grammar is simple since the focus will be on implementing IR representations
and optimizations.
There is only one lookahead for project 1 since one is enough to handle all the cases in the grammar.
A peek function may be added in project 2 to handle a special arguments case.
*/

static void error(){
    cerr << "line " << yylineno;
    cerr << ": syntax error at '" << yytext << "'" << endl;
    exit(EXIT_FAILURE);
}

static int nextWord(){
    int token = yylex();
    lexeme = yytext;
    return token;
}

void match(int token){
    if (word == token)
        word = nextWord();
    else
        error();
}

void argument(){
    if (word == STRING)
        match(STRING);
    else
        expression();
}

void argumentList(){
    argument();
    while (word == ','){
        match(',');
        argument();
    }
}

void primaryExpression(){
    switch (word){
        case '(':
            match('(');
            expression();
            match(')');
            break;
        case CHARLIT:
            match(CHARLIT);
            break;
        case NUM:
            match(NUM);
            break;
        case ID:
            match(ID);
            if (word == '('){
                match('(');
                if (word != ')')
                    argumentList();
                match(')');
            }
            if (word == '['){
                match('[');
                expression();
                match(']');
            }
            break;
    }
}

void unaryExpression(){
    if (word == '-'|| word == '!'){
        match(word);
        unaryExpression();
    }
    else
        primaryExpression();
}

void multiplicativeExpression(){
    unaryExpression();
    while (word == '/' || word == '*'|| word == '%') {
        match(word);
        unaryExpression();
    }
}

void additiveExpression(){
    multiplicativeExpression();
    while (word == '+' || word == '-') {
        match(word);
        multiplicativeExpression();
    }
}

void relationalExpression(){
    additiveExpression();
    while (word == '<' || word == '>' || word == LEQ || word == GEQ) {
        match(word);
        additiveExpression();
    }
}

void equalityExpression(){
    relationalExpression();
    while (word == EQL || word == NEQ) {
        match(word);
        relationalExpression();
    }
}

void andExpression(){
    equalityExpression();
    while (word == AND) {
        match(AND);
        equalityExpression();
    }
}

void expression() {
    andExpression();
    while (word == OR) {
        match(OR);
        andExpression();
    }
}

void specifier() {
    if (word == INT || word == CHAR)
        word = nextWord();
    else
        error();
}

void parameter() {
    specifier();
    match(  ID);
    if (word == '[') {
        match('[');
        match(']');
    }
}

void parameterList(){
    parameter();
    if (word == ','){
        match(',');
        parameterList();
    }
}

void parameters(){
    if (word == VOID)
        match(VOID);
    else
        parameterList();        
}

void declarator(){
    match(ID);
    if (word == '['){
        match('[');
        match(NUM);
        match(']');
    }
}

void moreDeclarators(){
    if (word == ','){
        match(',');
        declarator();
        moreDeclarators();
    }
}

void declaration(){
    specifier();
    declarator();
    moreDeclarators();
    match(';');
}

void declarations(){
    if (word == INT || word == CHAR){
        declaration();
        declarations();
    }
}

void assignment(){
    match(ID);
    switch (word){
        case '=':
            match('=');
            expression();
            break;
        case '[':
            match('[');
            expression();
            match(']');
            match('=');
            expression();
        case '(':
            match('(');
            if (word == ')'){
                match(')');
                return;
            }
            argumentList();
            match(')');
    }
}

void statement(){
    switch (word){
        case '{':
            match('{');
            statements();
            match('}');
            break;
        case IF:
            match(IF);
            match('(');
            expression();
            match(')');
            statement();
            if (word == ELSE){
                match(ELSE);
                statement();
            }
            break;
        case FOR:
            match(FOR);
            match('(');
            assignment();
            match(';');
            expression();
            match(';');
            assignment();
            match(')');
            statement();
            break;
        case WHILE:
            match(WHILE);
            match('(');
            expression();
            match(')');
            statement();
            break;
        case DO:
            match(DO);
            statement();
            match(WHILE);
            match('(');
            expression();
            match(')');
            statement();
            match(';');
            break;
        case RETURN:
            match(RETURN);
            expression();
            match(';');
            break;
        default:
            assignment();
            match(';');
    }
}

void statements(){
    while (word != '}')
        statement();
}

void globalDeclaration(){
    specifier();
    match(ID);
    string name = lexeme;
    if (word == '['){
        match('[');
        match(NUM);
        match(']');
        moreDeclarators();
        match(';');
        return;
    }
    else if(word == '('){
        match('(');
        parameters();
        match(')');
        match('{');
        declarations();
        statements();
        match('}');
        return;
    }
    moreDeclarators();
    match(';');
}

void translationUnit(){
    while (word != DONE)
        globalDeclaration();
}

int main(){
    word = nextWord();
    translationUnit();
    return EXIT_SUCCESS;
}