%{
#include "head.h"
#include "y.tab.h"
#include<iostream>
#include<string>
using namespace std;
extern YYSTYPE yylval;

%}

digit    [0-9]
letter    [A-Za-z]
word       {letter}({letter}|{digit})*
whitespace ([ \t]*)
compare [<>=]|(!=)|(>=)|(<=)|(like)
number {digit}+\.?(digit)*
%%

as {return AS;}
[\(]   {return LEFTPARENTHESIS;}
[\)]  {return RIGHTPARENTHESIS;}

select {return SELECT;}
from {return FROM;}
where {return WHERE;}
{whitespace} {}
and {yylval = new Logic("AND"); return LOGIC;}
or {yylval = new Logic("OR"); return LOGIC;}

, {return COMMA;}
; {return SEMICOLON;}

{compare} {yylval = new CompareOp(yytext);return COMPARE;}

{number} {yylval = new Number(yytext); return NUMBER;}


{word}  {yylval = new Word(yytext); return WORD;}
. {}
%%
int yywrap(void) {
return 1;
}

int yyerror(string s)
{
	cout << s << endl;
	return 1;
}

int m2ain()
{
yylex();
return 0;
}
