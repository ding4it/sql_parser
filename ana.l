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
logic (and)|(or)
%%

select {return SELECT;}
from {return FROM;}
where {return WHERE;}
{whitespace} {}
{logic} {yylval = new Logic(yytext); return LOGIC;}


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
