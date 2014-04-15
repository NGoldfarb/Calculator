#ifndef LOG_H
#define LOG_H


#include "Number.h"
#include "Basic.h"
#include "Expression.h"

using namespace std;

class Log : public Number{
public: //coef    base    argument
Log(Number*, Number*,Number*);
~Log();

Number* base;
Number* argument;
Number* coef;

string type;
Number* add(Number*) ;
Number* subtract(Number*) ;
Number* multiply(Number*) ;
Number* divide(Number*) ;
Number* expo(Number*);
int getValue() ;
char getCharValue() ;
Number* simplifyHelper() ;

string getType() ;
void print() ;
Number* getNum() ; //used for get argument in log
Number* getDen() ;
void setNum(Number*) ;
void setDen(Number*) ;
Number* simplify(Number*, int) ;
//for irrational class
Number* getCoef() ;
Number* getExp() ;
//for exponent class
Number* getBase() ;
// for expression
vector<Number*> getVect();

void simplify();
Number* log (Number*);
void setValue(int);
};








#endif /* LOG_H */
