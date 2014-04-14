#include "Basic.h"

Basic::Basic(int n){
    value = n;
    type = "Basic";
}
Basic::~Basic()
{

}

Number* Basic::add(Number* n){
    if(n->getType() == "Basic")
    {
    	Basic* x = new Basic(value + n->getValue());
    	delete n;
    	delete this;
    	return x;
   	}
    else   //currently only for n->getType() == "Fraction"
    {
    	Number* x = new Basic(n->getNum()->getValue() + value*n->getDen()->getValue());
    	Number* y = new Basic(n->getDen()->getValue());
    	Number* z = new Fraction(x, y);
    	delete n;
    	delete this;
    	return z;
    }
}

Number* Basic::subtract(Number* n){
    Basic* x = new Basic(value - n->getValue());
    delete n;
    delete this;
    return x;
}

Number* Basic::multiply(Number* n){  //updated for when n is a fraction
    if(n->getType() == "Basic")
    {
    	Basic* x = new Basic(value*n->getValue());
    	delete n;
    	delete this;
    	return x;
    }
    else  //only works for fraction, used else because we need a return statement to compile
    {
    	Basic* x = new Basic(value*n->getNum()->getValue());
    	Basic* y = new Basic(n->getDen()->getValue());  //created another Basic that won't get destructed when n does;
    	Fraction* z = new Fraction(x, y);
    	delete n;
    	delete this;
    	z->simplify();
    	return z;
    }
}

Number* Basic::divide(Number* n){   //only works for Basics and Fractions
    if(n->getType() == "Basic")
    {
    	if (value%n->getValue() == 0)
    	{
    		Basic* x = new Basic(value / n->getValue());
    		delete n;
    		delete this;
    		return x;
    	}
    	else
    	{
    		Number* a = new Fraction(this, n);
    		a->simplify();
    		return a;
    	}
    }
    else if (n->getType() == "Fraction")
    {
        Number* temp = n->getNum();
        n->setNum(n->getDen());
        n->setDen(temp);
        return multiply(n);
    }
    return n;  //need a return statement
}

Number* Basic::expo(Number* n){  //needs further implentation if the parameter number is not a basic or is negative etc
    if(n->getType() == "Basic")
    {
    	if(n->getValue() < 0)
    	{
    		return negExpo(n);
    	}
    	else
    	{
    		int answer = 1;
    		for(int i = 1; i <= n->getValue(); i++)
    		{
    		answer *= value;
    		}
    		Number* answer2 = new Basic(answer);
    		delete n;
    		delete this;
    		return answer2;
    	}
    }
    else if(n->getType() == "Fraction")
    {
    	Number* den = new Basic(n->getDen()->getValue());   //do first because n will be deleted
    	Number* base = expo(n->getNum());
    	Number* one = new Basic(1);
    	Number* power = new Fraction(one, den);
    	//Number* answer = new Exponent(base, power);    //need exponent class
    	//return answer;
    }
    return n;   //needs return statement outside if
}
Number* Basic::negExpo(Number* n)
{
	Number* num = new Basic(1);
	n->setValue(n->getValue() * (-1));
	Number* answer = num->divide(expo(n));
	return answer;
}

/*Number* Basic::simplifyHelper(){
    return this;
}*/

int Basic::getValue(){
    return value;
}

void Basic::setValue(int value)
{
	this->value = value;
}

void Basic::print(){  //changed so that prints out 1 values as well for fraction numerators etc

    //if (value != 1){
        cout << value;
    //}

}

string Basic::getType(){
    return type;
}

Number* Basic::getDen(){
    return this;
}

Number* Basic::getNum(){
    return this;
}

void Basic::setNum(Number* a){

}

void Basic::setDen(Number* a){
}

void Basic::simplify()
{
}
/*Number* Basic::simplify(Number* a, int n){
    return this;
}*/

Number* Basic::getCoef(){
    return this;
}

Number* Basic::getExp(){
    return this;
}

Number* Basic::getBase(){
    return this;
}


