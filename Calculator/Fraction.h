#ifndef FRACTION_H
#define FRACTION_H

#include <string>
#include <iostream>
#include "Number.h"

using namespace std;

class Fraction :public Number{
    public:

        Fraction(Number*, Number*);
        ~Fraction();

        Number* numerator;
        Number* denominator;
        string type;

        Number* getNum();
        Number* getDen();
        void setNum(Number*);
        void setDen(Number*);

        Number* add(Number*);
        Number* subtract(Number*);
        Number* multiply(Number*);
        Number* divide(Number*);
        int getValue();
        Number* simplify(Number*, int);
        Number* simplifyHelper();
        Number* expo(Number*);

        void print();
        string getType();
        char getCharValue(){ return '&'; }

        //for irrational class
        Number* getCoef();
        Number* getExp();

        //for exponent class
        Number* getBase();
};

#endif /* FRACTION_H */
