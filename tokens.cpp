#include "tokens.h"

Tnames::Tnames(Tname *t)
{
    tk = T_TNAMES;
    names = new vector<Tname*>();
    names->push_back(t);
}
Tnames::Tnames(Tnames *ts,Tname *t)
{
    tk = T_TNAMES;
    names = new vector<Tname*>(*ts->getNames());
    names->push_back(t);

}
string Tnames::getName()
{
    vector<Tname*>::iterator it;
    it=names->begin();
    string re;
    if(it!=names->end())
    {
        re = (*it)->getName();
        it++;
        for(; it!=names->end(); it++)
        {
            re += ", " + (*it)->getName();
        }
    }
    return re;
}


Tnames::~Tnames()
{
    delete names;
}

Tables::Tables(Table *t)
{
    tk = T_TABLES;
    tables = new vector<Table*>();
    tables->push_back(t);
}

Tables::Tables(Tables* ts,Table*t)
{
    tk = T_TABLES;
    tables = new vector<Table*>(*ts->getTables());
    tables->push_back(t);
}

string Tables::getName()
{
    vector<Table*>::iterator it;
    it=tables->begin();
    string re;
    if(it!=tables->end())
    {
        re = (*it)->getName();
        it++;
        for(; it!=tables->end(); it++)
        {
            re += ", " + (*it)->getName();
        }
    }
    return re;
}

Tables::~Tables()
{
    delete tables;
}
Where::Where(CompareUnit *l,CompareOp *c,CompareUnit *r)
{
    this->left = l;
    this->comp = c;
    this->right = r;
    tk=T_WHERE;
}

string Where::getName()
{
    return left->getName() + " " + comp->getName() + " " + right->getName();
}

Wheres::Wheres(Where *w)
{
    tk = T_WHERES;
    compares = new vector<Where*>();
    compares->push_back(w);
    logics = new vector<Logic*>();
}

Wheres::Wheres(Wheres *ws,Logic *l, Where *w)
{
    tk = T_WHERES;
    compares = new vector<Where*>(*ws->getCompares());
    compares->push_back(w);
    logics = new vector<Logic*>(*ws->getLogics());
    logics->push_back(l);
}

Wheres::~ Wheres()
{
    delete compares;
    delete logics;
}
string Wheres::getName()
{
    vector<Where*>::iterator it1;
    vector<Logic*>::iterator it2;

    it1= compares->begin();
    it2 = logics ->begin();
    string re;

    re = (*it1)->getName();
    it1++;
    for(; it1!=compares->end(); it1++,it2++)
    {
        re += " " + (*it2)->getName() +" " + (*it1)->getName();
    }

    return re;
}

Select::Select(Tnames *n,Tables *t,Wheres *w)
{
    tk = T_SELECTION;
    names = n;
    tables = t;
    wheres = w;
}
string Select::getName()
{
    string rs = "select " + names->getName() + " from "+ tables->getName();
    if(wheres != NULL)
    {
        rs += " where " + wheres->getName();
    }
    return rs;
}

Select::~Select()
{

}
void Select::printspace(int space)
{
    for(int i=0; i<space; i++)
        cout << "    ";
}

void Select::printTree()
{
    return printTree(0);
}
void Select::printTree(int space)
{
    printspace(space);
    cout << "+ QUERY/SELECT"<<endl;
    space +=1;
    printspace(space);
    cout << "+ SELECT" <<endl;
    printspace(space);
    cout << "+ FIELD" <<endl;
    space += 1;
    vector<Tname*> * ns = this->names->getNames();
    vector<Tname*>::iterator it1 = ns->begin();

    for(; it1!=ns->end(); it1++)
    {
        printspace(space);
        cout << "+ " << (*it1)->getName() <<endl;
    }
    space -= 1;

    printspace(space);
    cout << "+ FROM" <<endl;
    printspace(space);
    cout << "+ TABLE" <<endl;

    space += 1;

    vector<Table*> * ts = this->tables->getTables();
    vector<Table*>::iterator it2 = ts->begin();
    for(; it2!=ts->end(); it2++)
    {
        if(  (*it2)->getSelect() != NULL)
        {
            printspace(space);
            cout << "+ TABLE/SELECT AS " << (*it2)->getName() <<endl;
            space +=1;
            (*it2)->getSelect()->printTree(space);
            space -=1;
        }
        else
        {
            printspace(space);
            cout << "+ " << (*it2)->getName() <<endl;
        }
    }
    space -= 1;

    if(this->wheres != NULL)
    {
        printspace(space);
        cout << "+ WHERE" <<endl;
        space += 1;
        vector<Where*>::iterator it3;
        vector<Logic*>::iterator it4;

        it3= wheres->getCompares()->begin();
        it4 = wheres->getLogics() ->begin();
        printspace(space);
        cout << "+ COMPARE[ " << (*it3)->getOp()->getName() << " ]"<< endl;
        space +=1;
        printspace(space);
        cout << "+ " << (*it3)->getLeft()->getName() << endl;
        printspace(space);
        cout << "+ " << (*it3)->getRight()->getName() << endl;
        space -=1;
        it3++;
        space -=1;
        for(; it3!=wheres->getCompares()->end(); it3++,it4++)
        {
            space +=1;
            printspace(space);
            cout << "+ LOGICAL OPERATOR[ " << (*it4)->getName() << " ]"<<endl;
            printspace(space);
            cout << "+ COMPARE[ " << (*it3)->getOp()->getName() << " ]"<< endl;
            space +=1;
            printspace(space);
            cout << (*it3)->getLeft()->getName() << endl;
            printspace(space);
            cout << (*it3)->getRight()->getName() << endl;
            space -=1;
            space -=1;

        }



    }


}

