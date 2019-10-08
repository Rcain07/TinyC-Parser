#ifndef LEXER_H
#define LEXER_H
#include <string>

/*
COPYRIGHT 2019, Ryan Cain, All Rights Reserved.
This code is made by me for my academic use in the class COEN 259 with a few expecptions of code given from
a textbook/teacher.
*/

/* 
definitions for flex, mostly used as a way to get around some annoying Make errors
*/

extern char *yytext;
extern int yylineno, numerrors;

int yylex();
void report(const std::string &str, const std::string &arg = "");

#endif