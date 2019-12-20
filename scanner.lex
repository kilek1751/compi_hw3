%{

/* Declarations section */
#include <stdlib.h>
#include "source.hpp"
#include "parser.tab.hpp"
#include "hw3_output.hpp"






%}

%option yylineno
%option noyywrap

%%



void                            {yylval=new Void("VOID");return VOID;};
int                             {yylval=new Int(yytext,"INT");return INT;};
byte                            return BYTE;
b                               {yylval=new Byte(yytext,"B");return B;};
bool                            {yylval=new Bool(yytext,"BOOL");return BOOL;};
enum                            {yylval=new Enum(yytext,"ENUM");return ENUM;};
and                             return AND;
or                              return OR;
not                             return NOT;
true                            {yylval=new Bool(yytext,"BOOL");return TRUE;};
false                           {yylval=new Bool(yytext,"BOOL");return FALSE;};
return                          return RETURN;
else                            return ELSE;
if                              return IF;
while                           return WHILE;
break                           return BREAK;
continue                        return CONTINUE;
;                               return SC;
,                               return COMMA;
\(                              return LPAREN;
\)                              return RPAREN;
\{                              return LBRACE;
\}                              return RBRACE;
=                               return ASSIGN;
\<|>|<=|>=                       return RELOP;
==|!=                           return RELEQ;
[\*\/]                          return BINOPH;
[\+\-]                          return BINOPL;
[a-zA-z][a-zA-z0-9]*            {yylval=new Id(yytext,"ID");return ID;};
0|[1-9][0-9]*                   {yylval=new Int(yytext,"INT");return NUM;};
\"([^\n\r\"\\]|\\[rnt"\\])+\"	{yylval=new String(yytext,"STRING");return STRING;};
<<EOF>>                         return 0;
[\r\n\t ]|\/\/[^\r\n]*[\r|\n|\r\n]?	    ;
.                               {output::errorLex(yylineno);exit(0);};


%%

