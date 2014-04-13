#include "Fraction.h"
#include "Basic.h"
#include <stdexcept>
#include <math.h>   //for sqrt
//#include "Irrational.h"
using namespace std;

Fraction::Fraction(Number* a, Number* b){
    if (b->getValue() == 0){

        throw invalid_argument("Nice try, dividing by zero");
    }

    else{

        numerator = a;
        denominator = b;
        type = "Fraction";
    }
}
Fraction::~Fraction()
{
	delete numerator;
	delete denominator;
}

Number* Fraction::getNum(){
    return numerator;
}

Number* Fraction::getDen(){
    return denominator;
}

Number* Fraction::add(Number* a){

    if (a->getType() == "fraction"){
        Number* x = new Basic(denominator->getValue()*a->getDen()->getValue());
        Number* y = new Basic(numerator->getValue()*a->getDen()->getValue() + denominator->getValue()*a->getNum()->getValue());
        Number* z = new Fraction(y, x);
        return z;
        }


    else{ return this; }
}

Number* Fraction::subtract(Number* a){

    if (a->getType() == "fraction"){
        Number* x = new Basic(denominator->getValue()*a->getDen()->getValue());
        Number* y = new Basic(numerator->getValue()*a->getDen()->getValue() - denominator->getValue()*a->getNum()->getValue());
        Number* z = new Fraction(y, x);
        return z;
    }
    return this;
}

Number* Fraction::multiply(Number* a){
    if (a->getType() == "fraction"){
        Basic* x1 = new Basic(numerator->getValue()*a->getNum()->getValue());
        Basic* x2 = new Basic(denominator->getValue()*a->getDen()->getValue());
        Number* n = new Fraction(x1, x2);
        return n->simplifyHelper();
    }

    if (a->getType() == "basic"){
        Basic* b = new Basic(a->getValue()*numerator->getValue());
        Number* x = b;
        Number* f = new Fraction(x, denominator);
        return f->simplifyHelper();
    }

    if (a->getType() == "irrational"){
        /*Basic* j = new Basic(numerator->getValue()*a->getCoef()->getValue());
        Number* n = j;
        Number* i = new Irrational(a->getCharValue(), n, a->getExp());
        Number* k = new Fraction(i, denominator);
        return k;*/


    }

    return a;
}

Number* Fraction::divide(Number* a){
    return this;
}

Number* Fraction::expo(Number* a){
    return this;
}

Number* Fraction::simplifyHelper(){    // do we want this to be void?
    return simplify(this, 9);
}

Number* Fraction::simplify(Number* a,int n){    // do we want this to be void?
        if (n == 1){
            return a;
        }
        if (denominator->getValue() == 1){
            Number* b = new Basic(numerator->getValue());
            delete this;  //I think we need this
            return b;
        }

        if (numerator->getValue()%n == 0 && denominator->getValue()%n == 0){
            Number* j = new Basic(numerator->getValue() / n);
            Number* l = new Basic(denominator->getValue() / n);
            a->setNum(j);
            a->setDen(l);
            return a->simplify(a, n);
        }
        else{
            return a->simplify(a, n - 1);
        }
    }



string Fraction::getType(){
    return type;
}

void Fraction::print(){
    if(denominator->getValue()!=1){
        cout << '(';
        numerator->print();
        cout << '/';
        denominator->print();
        cout << ')';
    }
    else{
        cout<<numerator->getValue();
    }
}

int Fraction::getValue(){
    return 1;
}

void Fraction::setNum(Number* a){
    numerator = a;

}

void Fraction::setDen(Number* a){
    denominator = a;
}

Number* Fraction::getCoef(){
    return this;
}

Number* Fraction::getExp(){
    return this;
}

Number* Fraction::getBase(){
    return this;
}




