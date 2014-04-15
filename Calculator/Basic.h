#ifndef BASIC_H
#define BASIC_H

#include <string>
#include <iostream>
#include "Number.h"
#include "Fraction.h"
#include <math.h>

using namespace std;

class Basic : public Number{
    public:
        int value;
        string type;

        Basic(int);
        virtual ~Basic();

        Number* add(Number*);
        Number* subtract(Number*);
        Number* multiply(Number*);
        Number* divide(Number*);
        int getValue();
        void setValue(int);
        //Number* simplifyHelper();
        //Number* simplify(Number*,int);
        void simplify();
        Number* expo(Number*);
        Number* negExpo(Number*);
        Number* log(Number*);

        void factor(int, vector<int>&);
        void factorHelper(int, vector<int>&);
        bool isPrime(int);

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
