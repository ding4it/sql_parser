#ifndef TOKENS_H
#define TOKENS_H

#include<iostream>
#include <string>
#include <vector>
using namespace std;

enum TokenEnum
{
    T_NUMBER,
    T_WORD,
    T_SELECTION,
    T_TNAMES,
    T_TABLES,
    T_WHERES,
    T_TNAME,
    T_TABLE,
    T_WHERE,
    T_LOGIC,
    T_COMPAREUNIT,
    T_COMPAREOPERATION
};

class Token
{
protected:
    TokenEnum tk;
    string name;
public:
    virtual string  getName(){return this->name;}

};

class Select;
class Tnames;
class Tables;
class Wheres;

class Number:public Token
{
public:
    Number(string n){this->name = n;tk=T_NUMBER;}
};


class Word:public Token
{

public:
    Word(string n){this->name = n;tk=T_WORD;}
};

class Tname :public Token
{
public:
    Tname(string n){this->name = n;tk=T_TNAME;}

};


class Table:public Token
{
private:
    Select * s;
public:
    Select * getSelect(){return s;}
    Table(string n){this->s == NULL;this->name = n;tk=T_TABLE;}
    Table(Select *s,string n){this->s = s;this->name = n;tk=T_TABLE;}

};

class CompareUnit:public Token
{
public:
    CompareUnit(string u){this->name = u;tk=T_COMPAREUNIT;}
};

class CompareOp:public Token
{

public:
    CompareOp(string n){this->name= n;tk=T_COMPAREOPERATION;}
};

class Logic:public Token
{

public:
    Logic(string n){this->name = n;tk=T_LOGIC;}
};

class Where:public Token
{
private:
    CompareUnit *left;
    CompareOp *comp;
    CompareUnit *right;
public:
    CompareUnit * getLeft(){return left;}
    CompareUnit * getRight(){return right;}
    CompareOp * getOp(){return comp;}
    Where(CompareUnit *l,CompareOp *c,CompareUnit *r);
    string getName();
};

class Tnames : public Token
{
private:
    vector<Tname*> *names;

public:
    vector<Tname*> * getNames(){return this->names;}
    Tnames(Tname *t);
    Tnames(Tnames*,Tname*);
    ~Tnames();
    string getName();
};

class Tables : public Token
{
private:
    vector<Table*> *tables;

public:
    vector<Table*> * getTables(){return this->tables;}
    Tables(Table *t);
    Tables(Tables*,Table*);
    ~Tables();
    string getName();

};

class Wheres :public Token
{
private:

    vector<Where*> *compares;
    vector<Logic*> *logics;

public:
    vector<Where*> * getCompares(){return this->compares;}
    vector<Logic*> * getLogics(){return this->logics;}
    Wheres(Where *w);
    Wheres(Wheres *ws,Logic *l, Where *w);
    ~ Wheres();
    string getName();

};

class Select :public Token
{
private:
    Tnames *names;
    Tables *tables;
    Wheres *wheres;
    void printspace(int space);

public:
    Select(Tnames *n,Tables *t,Wheres *w);
    ~Select();
    string getName();
    void printTree();
    void printTree(int space);


};



#endif // TOKENS_H
