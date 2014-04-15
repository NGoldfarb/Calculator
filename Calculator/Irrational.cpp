#include "Irrational.h"



Irrational::Irrational(char c,Number* n, Number* n1){
value = c;
type = "irrational";

b1 = new Basic(1);
coef = n;
exp = n1;
}

Number* Irrational::add(Number* a){
	if (value == a->getCharValue()&&exp == a->getExp()){
		if (coef->getType() == "Basic"&& a->getCoef()->getType() == "Basic"){
                     int aCoef =a->getCoef()->getValue();
                     int newCoef =getCoef()->getValue()+ aCoef;
			Number* b1 = new Basic(newCoef);
			Number* b2 = new Irrational(value, b1, exp);
			return b2;
		}
		if (coef->getType() == "Fraction"&& a->getCoef()->getType() == "Fraction"){
                       int d = getCoef()->getValue();
                       int e = a->getCoef()->getValue();
                Number* newCoef = new Basic(d);
                Number* aCoef = new Basic(e);
                Number*k= new Fraction(newCoef,aCoef);
               
			
			Number* b2 = new Irrational(value,k, exp);
                      
			
return b2;
		}

	}
	return b1;
}



Number* Irrational::subtract(Number* a){	
if (value == a->getCharValue() && exp == a->getExp()){
		if (coef->getType() == "Basic"&&a->getCoef()->getType() == "Basic"){
                     int aCoef =a->getCoef()->getValue();
                     int newCoef=getCoef()->getValue()-aCoef;
			Number* b1 = new Basic(newCoef);
			Number* b2 = new Irrational(value, b1, exp);
			return b2;
		}
		if (coef->getType() == "Fraction"&&a->getCoef()->getType() == "Fraction"){
                int d = getCoef()->getValue();
                       int e = a->getCoef()->getValue();
                Number* newCoef = new Basic(d);
                Number* aCoef = new Basic(e);
                Number*k= new Fraction(newCoef,aCoef);
               
			
			Number* b2 = new Irrational(value,k, exp);
                      
			
return b2;
		
			
		}

	}
	return b1;
}
Number* Irrational::multiply(Number* a){

	if (a->getCoef()->getType() == "Basic"&&getCoef()->getType()=="Basic"){

             int aCoef =a->getCoef()->getValue();
             int newCoef= getCoef()->getValue() * aCoef;
		Number* n = new Basic(newCoef);
              int newExp = getExp()->getValue() + a->getExp()->getValue();
		Number* e = new Basic(newExp);
             Number* x = new Irrational(value, n, e);
              
		return x;
	}
	return b1;
}

Number* Irrational::divide(Number* a){
cout<<"hey";
	if (a->getCoef()->getType() == "Basic"&&getCoef()->getType()=="Basic"){
cout<<"yes";
	      int aCoef =a->getCoef()->getValue();
             int newCoef=getCoef()->getValue();
             Number*a= new Basic(aCoef);
             Number*b= new Basic(newCoef);
              Number* e= new Fraction(b,a);
 e->simplify();
return e ;
}

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
vector<Number*> Irrational::getVect()
{
	vector<Number*> answer;
	return answer;
}