%option nounput 
%option yylineno 
%option noyywrap
%x COMMENT_MULTI
%{
#include <iostream>
#include "TOKENS.h"
#include "lexer.h"
using namespace std;

/*
COPYRIGHT 2019, Ryan Cain, All Rights Reserved.
This code is made by me for my academic use in the class COEN 259 with a few expecptions of code given from
a textbook/teacher.
*/


/*
We use flex in this class to quickly set up regular expressions that will pattern match all of the lexical
analysis for our compiler.


*/
%}

%%

(\ |\t|\n|\f|\v|\r)+    {}
[0-9]+                  {return NUM;}
\"(\\[^\n]|[^\\\n"])*\" {return STRING;}
\'(\\[^\n]|[^\\\n'])*\' {return CHARLIT;}
auto                    {return AUTO;}
break                   {return BREAK;}
case                    {return CASE;}
char                    {return CHAR;}
const                   {return CONST;}
continue                {return CONTINUE;}
default                 {return DEFAULT;}
do                      {return DO;}
double                  {return DOUBLE;}
else                    {return ELSE;}
enum                    {return ENUM;}
extern                  {return EXTERN;}
float                   {return FLOAT;}
for                     {return FOR;}  
goto                    {return GOTO;}
if                      {return IF;}
int                     {return INT;}
long                    {return LONG;}
register                {return REGISTER;}
return                  {return RETURN;}
short                   {return SHORT;}
signed                  {return SIGNED;}
sizeof                  {return SIZEOF;}
static                  {return STATIC;}
struct                  {return STRUCT;}
switch                  {return SWITCH;}
typedef                 {return TYPEDEF;}
union                   {return UNION;}
unsigned                {return UNSIGNED;}
void                    {return VOID;}
volatile                {return VOLATILE;}
while                   {return WHILE;}

[=<>+*/%!()[\]{};\-,]   {return *yytext;}

[_a-zA-Z][_a-zA-Z]*     {return ID;}
"||"                    {return OR;}
"&&"                    {return AND;}
"=="                    {return EQL;}
"!="                    {return NEQ;}
"<="                    {return LEQ;}
">="                    {return GEQ;}
"++"                    {return INC;}
"--"                    {return DEC;}



<INITIAL>"/*"           {BEGIN(COMMENT_MULTI);}
<COMMENT_MULTI>"*/"     {}
<COMMENT_MULTI>.        {} 
<COMMENT_MULTI>\n       {} 

.                       {return ERROR;}

%%