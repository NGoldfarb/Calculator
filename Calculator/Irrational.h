
#ifndef IRRATIONAL_H
#define IRRATIONAL_H


#include "Number.h"
#include "Basic.h"
#include "Expression.h"

using namespace std;

class Irrational:public Number{
public:
Number* b1;
string type;
char value;
Number* coef;
Number* exp;
//                coef      exp
Irrational(char, Number*,Number*);
~Irrational();

Number* add(Number*);
Number* subtract(Number*);
Number* multiply(Number*);
Number* divide(Number*);
char getCharValue();
Number* simplifyHelper();
Number* expo(Number*);
Number* log(Number*);
string getType();
void print();
Number* getNum();
Number* getDen();
void setNum(Number*);
void setDen(Number*);
Number* simplify(Number*, int);
int getValue();
void setValue(int);
void simplify();

//for irrational class
Number* getCoef();
Number* getExp();

//for exponent class
Number* getBase();

vector<Number*> getVect();

};












#endif /* IRRATIONAL_H */





