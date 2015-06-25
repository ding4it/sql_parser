%{
#include "head.h"
#include<iostream>
#include<string>
using namespace std;

extern int yylex(void);
extern int yyparse(void);
extern int yyerror(string);

%}
%token SELECT FROM WHERE WORD COMMA SEMICOLON COMPARE NUMBER LOGIC LEFTPARENTHESIS RIGHTPARENTHESIS AS

%%
all:
    select SEMICOLON
    {
    ((Select*) $$)->printTree();
    return 0;
    }
select:
    SELECT tnames FROM tables
{
    $$ = new Select((Tnames*)$2,(Tables*)$4,NULL);
}

    | SELECT tnames FROM tables WHERE wheres
{
    $$ = new Select((Tnames*)$2,(Tables*)$4,(Wheres*)$6);
}

tnames:
    tname
    {    $$ = new Tnames((Tname*)$1);}
    | tnames COMMA tname
    {    $$ = new Tnames((Tnames*)$1,(Tname*)$3);}

tname:
    WORD
    {    $$ = new Tname($1->getName());    }


tables:
    table
    {    $$ = new Tables((Table*)$1);    }
    | tables COMMA table
    {    $$ = new Tables((Tables*)$1,(Table*)$3);    }
    | select
    {}


table:
    WORD
    {
    $$ = new Table($1->getName());    }
    | LEFTPARENTHESIS select RIGHTPARENTHESIS AS WORD
    {
        $$ = new Table((Select*)$2,$5->getName());
    }

wordornum:
    WORD
    {    $$ = $1;    }
    | NUMBER
    {    $$ = $1;    }

comp:
    wordornum COMPARE wordornum
    {
        $$ = new Where( new CompareUnit($1->getName()),
                        new CompareOp($2->getName()),
                        new CompareUnit($3->getName()));
    }

wheres:
    comp
    {    $$ = new Wheres((Where*)$1);    }
    | wheres LOGIC comp
    {    $$ = new Wheres((Wheres*)$1,(Logic*)$2,(Where*)$3);}

%%



int main()
{
    yyparse();
    return 0;
}
