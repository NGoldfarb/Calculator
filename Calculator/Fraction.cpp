#include "Fraction.h"
#include "Basic.h"
#include <stdexcept>
//#include <math.h>   //for sqrt
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

    if (a->getType() == "Fraction"){
        Number* x = new Basic(denominator->getValue()*a->getDen()->getValue());
        Number* y = new Basic(numerator->getValue()*a->getDen()->getValue() + denominator->getValue()*a->getNum()->getValue());
        Number* z = new Fraction(y, x);
        delete a;
        delete this;
        z->simplify();
        return z;
        }
    else //currently only for type Basic
    {
    	Number* x = new Basic(numerator->getValue() + a->getValue()*denominator->getValue());
    	Number* y = new Basic(denominator->getValue());
    	Number* z = new Fraction(x, y);
    	delete a;
    	delete this;
    	return z;   //don't need to simplify in this case
    }


    //else{ return this; }
}

Number* Fraction::subtract(Number* a){

    if (a->getType() == "Fraction"){
        Number* x = new Basic(denominator->getValue()*a->getDen()->getValue());
        Number* y = new Basic(numerator->getValue()*a->getDen()->getValue() - denominator->getValue()*a->getNum()->getValue());
        Number* z = new Fraction(y, x);
        return z;
    }
    return this;
}

Number* Fraction::multiply(Number* a){
    if (a->getType() == "Fraction"){
        Basic* x1 = new Basic(numerator->getValue()*a->getNum()->getValue());
        Basic* x2 = new Basic(denominator->getValue()*a->getDen()->getValue());
        Number* n = new Fraction(x1, x2);
        delete a;
        delete this;
        n->simplify();
        return n;
    }

    else if (a->getType() == "Basic"){
        Basic* b = new Basic(a->getValue()*numerator->getValue());
        Basic* c = new Basic(denominator->getValue());
        Number* f = new Fraction(b, c);
        f->simplify();
        return f;
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

Number* Fraction::divide(Number* a)
{
	if(a->getType() == "Basic")
	{
		setDen(denominator->multiply(a));  //should delete denominator and a
		simplify();
		return this;
	}
	else if(a->getType() == "Fraction")
	{
		Number* temp = a->getNum();
		a->setNum(a->getDen());
		a->setDen(temp);
		return multiply(a);
	}
	return a;  //need a return statement outside if's
}

Number* Fraction::expo(Number* n){
    if(n->getType() == "Basic")
    {
    	Number* powTemp = new Basic(n->getValue());   //since n will be deleted
    	Number* num = numerator->expo(n);   //n is gone after this
    	Number* den = denominator->expo(powTemp);
    	Number* answer = new Fraction(num, den);
    	//delete this;   //doesn't work when this line is uncommented, not sure why, might cause memory leak
    	return answer;
    }
    else if(n->getType() == "Fraction")
    {
    	Number* base = expo(n->getNum());   //not sure how this interacts with n->getDen() below
    	Number* one = new Basic(1);
    	Number* power = new Fraction(one, n->getDen());
    	//Number* answer = new Exponent(base, power);  //need exponent class
    	//return answer;
    }
    return n;   //need a return statement outside ifs
}

Number* Fraction::log(Number* a)
{
	return a;
}

/*Number* Fraction::simplifyHelper(){    // do we want this to be void? - Zach
    return simplify(this, 9);
}*/

void Fraction::simplify()
{
	int gcd = this->getGCD(numerator->getValue(), denominator->getValue());
	numerator->setValue(numerator->getValue()/gcd);
	denominator->setValue(denominator->getValue()/gcd);
}
int Fraction::getGCD(int min, int max)   //making this static would be better but we can figure that out later
{
	if(max%min == 0)
	{
		return min;
	}
	else
	{
		return getGCD((max%min), min);
	}
}

/*Number* Fraction::simplify(Number* a,int n){    // do we want this to be void? - Zach
        if (n == 1){
            return a;
        }
        if (denominator->getValue() == 1){
            Number* b = new Basic(numerator->getValue());
            delete this;  //I think we need this - Zach
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
*/


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
void Fraction::setValue(int a)
{
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




