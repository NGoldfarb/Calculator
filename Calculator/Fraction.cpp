#include "Fraction.h"
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

    if (a->getType() == "Irrational"){   //still need to deal with deletes
        Number* num = new Basic(numerator->getValue()*a->getCoef()->getValue());
        Number* coef = new Fraction(num, denominator);
        Number* answer = new Irrational(a->getCharValue(), coef, a->getExp());
        return answer;


    }

    return a;
}

Number* Fraction::divide(Number* a)
{
	if(a->getType() == "Basic")
	{
		if(a->getValue() == 0)
		{
			throw invalid_argument("You can't divide by zero!");
		}
		else
		{
			setDen(denominator->multiply(a));  //should delete denominator and a
			simplify();
			return this;
		}
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
    	if(n->getNum()->getValue() != 1)  // if power is not of form 1/m
    	{
    		Number* powerNum = new Basic(n->getNum()->getValue());  //since n gets deleted next line
    		Number* nsNum = new Basic(n->getNum()->getValue());  //need this because we can't call n->divide(n->getNum())
    		Number* newPower = n->divide(nsNum);  //makes newPower into 1/denominator
    		Number* newFrac = this->expo(powerNum);  //raises this to n's numerator, deletes this and powerNum
    		return newFrac->expo(newPower);
    	}
    	else  //if power is of form 1/m
    	{  //might be better to use copy constructor
    		Number* secondPowerNum = new Basic(1);      //since exponenet will get deleted
    		Number* secondPowerDen = new Basic(n->getDen()->getValue());
    		Number* secondPower = new Fraction(secondPowerNum, secondPowerDen);
    		Number* newNum = numerator->expo(n);   //n gets deleted
    		Number* newDen = denominator->expo(secondPower);  //secondPower gets deleted
    		Number* answer = new Fraction(newNum, newDen);
    		delete this;
    		delete n;
    		return answer;
    	}

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
	if(denominator->getValue() < 0)
	{
		denominator->setValue(denominator->getValue() * -1);
		numerator->setValue(numerator->getValue() * -1);
	}
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
    return 69;
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
vector<Number*> Fraction::getVect()
{
	vector<Number*> answer;
	return answer;
}
Number* Fraction::simplifyHelper()
{
	return this;
}




