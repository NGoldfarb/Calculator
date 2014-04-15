#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include <iostream>
#include "Number.h"
#include "Basic.h"

using namespace std;

class Expression : public Number{
public:
Expression(vector<Number*>);
~Expression();

vector<Number*> expr;

string type;
Number* add(Number*) ;
Number* subtract(Number*) ;
Number* multiply(Number*) ;
Number* divide(Number*) ;
int getValue() ;
char getCharValue() ;
Number* simplifyHelper() ;
Number* expo(Number*) ;
string getType() ;
void print() ;
Number* getNum() ;
Number* getDen() ;
void setNum(Number*) ;
void setDen(Number*) ;
Number* simplify(Number*, int) ;
//for irrational class
Number* getCoef() ;
Number* getExp() ;
//for exponent class
Number* getBase() ;
//for expression
vector<Number*> getVect();

void setValue(int);
Number* log(Number*);
void simplify();

};




#endif /* EXPRESSION_H */
