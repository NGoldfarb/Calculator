#ifndef BASIC_H
#define BASIC_H

#include <string>
#include <iostream>
#include "Number.h"
#include "Fraction.h"

using namespace std;

class Basic : public Number{
    public:
        int value;
        string type;

        Basic(int);
        ~Basic();

        Number* add(Number*);
        Number* subtract(Number*);
        Number* multiply(Number*);
        Number* divide(Number*);
        int getValue();
        Number* simplifyHelper();
        Number* simplify(Number*,int);
        Number* expo(Number*);

        void print();
        string getType();

        Number* getNum();
        Number* getDen();
        void setNum(Number*);
        void setDen(Number*);
        char getCharValue(){ return '$'; }

        //for irrational class
        Number* getCoef();
        Number* getExp();

        //for exponent class
        Number* getBase();

};


#endif /* BASIC_H_ */
