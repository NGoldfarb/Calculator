#include "Irrational.h"



Irrational::Irrational(char c,Number* n, Number* n1){
value = c;
type = "irrational";

//b1 = new Basic(1);
coef = n;
exp = n1;
}

Number* Irrational::add(Number* a){
	cout<<"test";

	/*if(this->getType() == a->getType())
	{
		if(this->exp == a->getExp())
		{
			Number* coef = new Basic(this->coef->add(a->getCoef()));
			Number* b = new Irrational(this->value,coef,this->exp);
		}
	}

	return b;*/











	/*
	if (this->value == a->getCharValue()&&this->exp == a->getExp()){
		if (this->coef->getType() == "basic"&&a->getCoef()->getType() == "basic"){
			Number* b1 = new Basic(coef->add(a->getCoef())->getValue());
			Number* b2 = new Irrational(this->value, b1, this->exp);
			b1->print();
			return b2;
		}
		else if (this->coef->getType() == "fraction"&&a->getCoef()->getType() == "fraction"){
			Number* b1 =this->coef->add(a->getCoef());
			b1->print();
			Number* b2 = new Irrational(this->value, b1, this->exp);
			return b2;
		}

	}*/
	cout<<"test 2";
	return b1;
}

Number* Irrational::subtract(Number* a){
if (value == a->getCharValue() && exp == a->getExp()){
if (coef->getType() == "basic"&&a->getCoef()->getType() == "basic"){
Number* b1 = new Basic(coef->subtract(a->getCoef())->getValue());
Number* b2 = new Irrational(value, b1, exp);
return b2;
}
if (coef->getType() == "fraction"&&a->getCoef()->getType() == "fraction"){
Number* b1 = coef->subtract(a->getCoef());
Number* b2 = new Irrational(value, b1, exp);
return b2;
}

}
return b1;
}

Number* Irrational::multiply(Number* a){

if (a->getType() == "basic"){
Number* x = new Irrational(value, coef->multiply(a), exp);
return x;
}
return b1;
}

Number* Irrational::divide(Number* a){
return b1;
}

Number* Irrational::expo(Number* a){
return b1;
}

Number* Irrational::log(Number* a)
{
	return a;
}

char Irrational::getCharValue(){
return value;
}

Number* Irrational::simplifyHelper(){
return b1;
}

string Irrational::getType(){
return type;
}

void Irrational::print(){
	if (exp->getValue() == 1&&coef->getValue() != 1){

			coef->print();

			if(value == 'p')
			{
				cout<< "pi";
			}
			else //e
			cout << value;
	}
	else if (coef->getValue() == 1 && exp->getValue() != 1){
		if(value == 'p')
		{
			cout<< "pi";
		}
		else //e
			cout << value;
			cout << '^';
			exp->print();
	}
	else if (coef->getValue() == 1 && exp->getValue() == 1){
		if(value == 'p')
		{
			cout<< "pi";
		}
		else //e
		cout << value;
	}
	else{
		coef->print();
		if(value == 'p')
		{
			cout<< "pi";
		}
		else //e
		cout << value;
		cout << '^';
		exp->print();
	}
}

Number* Irrational::getNum(){
return b1;
}

Number* Irrational::getDen(){
return b1;
}

void Irrational::setNum(Number*){

}

void Irrational::setDen(Number*){

}

Number* Irrational::simplify(Number* a, int n){
return b1;
}

int Irrational::getValue(){
return 1;
}

Number* Irrational::getCoef(){
return coef;
}

Number* Irrational::getExp(){
return exp;
}

Number* Irrational::getBase(){
return this;
}

void Irrational::setValue(int n){
return;
}

void Irrational::simplify()
{
}

Irrational::~Irrational(){

delete this;
}
