#include "Basic.h"

Basic::Basic(int n){
    value = n;
    type = "Basic";
}
Basic::~Basic()
{

}

Number* Basic::add(Number* n){
    Basic* x = new Basic(value + n->getValue());
    delete n;
    delete this;
    return x;
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
    	return z;
    }
}

Number* Basic::divide(Number* n){   //only works for Basics
    if (value%n->getValue() == 0){
        Basic* x = new Basic(value / n->getValue());
        delete n;
        delete this;
        return x;
    }

    else{
        Basic* y = new Basic(n->getValue());
        Number* a = new Fraction(this, y);
        delete n;
        a->simplify();
        return a;

    }
}

Number* Basic::expo(Number* n){  //needs further implentation if the parameter number is not a basic or is negative etc
    int a = 1;
    int b = 1;
    while (a < n->getValue() + 1){
        b *= value;
        a++;
    }
    Basic* d = new Basic(b);
    return d;
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


