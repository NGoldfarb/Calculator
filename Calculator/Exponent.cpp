#include "Exponent.h"

Exponent::Exponent(Number* a, Number* b, Number* c){
	base = b;
	exp = c;
	coef = a;
	type = "exponent";
}
Exponent::~Exponent()
{
	delete base;
	delete exp;
	delete coef;
}


Number* Exponent::add(Number* a){
	if (type == "exponent" && a->getType() == "exponent"){
		if (base == a->getBase() && exp == a->getExp()){
			Number* x = coef->add(a->getCoef());
			Number* e = new Exponent(x, base, exp);
			return e;
		}
	}

	return this;
}

Number* Exponent::subtract(Number* a){
	if (type == "exponent" && a->getType() == "exponent"){
		if (base == a->getBase() && exp == a->getExp()){
			Number* x = coef->subtract(a->getCoef());
			Number* e = new Exponent(x, base, exp);
			return e;
		}

	}
	return this;
}

Number* Exponent::multiply(Number* a){
	if (type == a->getType() && getBase() == a->getBase())
	{
		Number* x = coef->multiply(a->getCoef());
		Number* y = exp->add(a->getExp());
		Number* z = new Exponent(x, base, y);
		return z;

	}
	if (a->getType() == "basic" && base->getValue() == a->getValue()){
		//	Number* x = new Exponent(coef, base, exp->getValue()+1)
	}
	return this;
}

Number* Exponent::divide(Number* a){
	if (type == a->getType() && getBase() == a->getBase())
	{
		Number* x = coef->divide(a->getCoef());
		Number* y = exp->subtract(a->getExp());
		Number* z = new Exponent(x, base, y);
		return z;
	}
	return this;
}

Number* Exponent::expo(Number* a){
	if (a->getType() == "exponent")
	{
		Number* x = exp->multiply(a->getExp());
	}
	return this;
}

int Exponent::getValue(){
	return simplifyHelper()->getCoef()->getValue();
}

char Exponent::getCharValue(){
	return '$';
}

Number* Exponent::simplifyHelper(){
	if (base->getType() == "basic"&&exp->getType() == "basic")
	{
		if (exp->getValue() <= -1)
		{
			Number* b = new Basic(1);
			Number* a = new Exponent(coef, base->expo(exp), b);
			Number* c = new Exponent(b, a->getBase()->multiply(coef), b);
			Number* n = new Fraction(coef, c->getBase());
			return n;
		}
		else if (getType() == "fraction" && exp->getNum()->divide(getDen())->getValue() < 1)
		{
			if (exp->getNum()->getValue() / exp->getDen()->getValue() < 0 && exp->getNum()->getValue() / exp->getDen()->getValue() > -1)
			{
				Number* b = new Basic(1);
				Number* a = new Exponent(coef, base->expo(exp), b);
				Number* c = new Exponent(b, a->getBase()->multiply(coef), b);
				Number* n = new Fraction(coef, c->getBase());
				return n;
			}
			else if (exp->getNum()->getValue() / exp->getDen()->getValue() > 0 && exp->getNum()->getValue() / exp->getDen()->getValue() < 1)
			{

			}
		}
		else {
			Number* b = new Basic(1);
			Number* a = new Exponent(coef, base->expo(exp), b);
			Number* c = new Exponent(b, a->getBase()->multiply(coef), b);
			return c;
		}

	}

	/*if (base->getType() == "basic" && exp->getType() == "basic")
	{
		int temp = base->getValue();
		int c;
		Number* a = new Basic(1);
		Number* b = new Exponent(coef, base, exp);
		for (int i = 0; i < exp->getValue(); i++)
		{
			int c = base->getValue() * temp;
			Number* e = new Basic(c);
			Number* d = new Exponent(a, e, a);
			return d;
		}



	}
	*/
	return this;
}

Number* Exponent::simplify(Number*, int){
	if (getExp()->getValue() < 0)
	{
		int i = getExp()->getValue();
		while (i != 1){
			base = base->divide(getBase());
			i++;
		}
	}
	else if (getExp()->getValue() > 0 && getExp()->getValue() < 1)
	{

	}
	else{
		int j = getExp()->getValue();
		while (j != 0)
		{
			base = base->multiply(getBase());
			j--;
		}
	}
	Number* z = exp->subtract(exp + 1);
	Number* y = new Exponent(coef, base, z);
	return y;
	}





string Exponent::getType(){
	return type;
}

void Exponent::print(){
	Number* j = simplifyHelper();
	if (coef->getValue() ==! 1)
	{
		j->getCoef()->print();
	}
	j->getBase()->print();
	if (exp ==! 1)
	{
		cout << '^';
		j->getExp()->print();
	}
}

Number* Exponent::getNum(){
	return this;
}

Number* Exponent::getDen(){
	return this;
}

void Exponent::setNum(Number*){

}

void Exponent::setDen(Number*){

}

Number* Exponent::getCoef(){


	return coef;

}

Number* Exponent::getExp(){
	return exp;
}

Number* Exponent::getBase(){
	return base;
}

vector<Number*> Exponent::getVect(){
	Number* y = new Basic(1);
	vector<Number*> x;
	x.push_back(y);
	return x;
}

void Exponent::factor(int num, vector<int>& primeFactors)  //at end, primeFactors contains prime factors of num in ascending order
{
	primeFactors.clear();
	return factorHelper(num, primeFactors);
}
void Exponent::factorHelper(int num, vector<int>& primeFactors)
{
	if (isPrime(num))
	{
		primeFactors.push_back(num);
	}
	else
	{
		int i = 2;
		while (!isPrime(i) || num%i != 0)
		{
			i++;
		}
		primeFactors.push_back(i);
		factorHelper(num / i, primeFactors);
	}
}
bool Exponent::isPrime(int num)
{
	double squareRoot = sqrt(num);
	for (int i = 2; i <= squareRoot; i++)
	{
		if (num%i == 0)
		{
			return false;
		}
	}
	return true;
}

void Exponent::setValue(int a)
{

}
void Exponent::simplify()
{

}
Number* Exponent::log(Number* num)
{
	return this;
}
/*
Number* Exponent::negExpo(Number* n)
{
	Number* num = new Basic(1);
	n->setValue(n->getValue() * (-1));
	Number* answer = num->divide(expo(n));
	return answer;
}
*/
/*

Number* Exponent::expon(Number* n){  //needs further implentation if the parameter number is not a basic or is negative etc
	if (n->getType() == "Basic")
	{
		if (n->getValue() < 0)
		{
			return negExpo(n);
		}
		else
		{
			int answer = 1;
			for (int i = 1; i <= n->getValue(); i++)
			{
				answer *= value;
			}
			Number* answer2 = new Basic(answer);
			delete n;
			delete this;
			return answer2;
		}
	}
	else if (n->getType() == "Fraction")
	{
		if (n->getNum()->getValue() != 1)
		{
			Number* den = new Basic(n->getDen()->getValue());   //do first because n will be deleted
			Number* base = expo(n->getNum());
			Number* one = new Basic(1);
			Number* power = new Fraction(one, den);
			return base->expo(power);
		}
		else
		{
			int baseInt = value;
			int root = n->getDen()->getValue();
			vector<int> primeFactors;
			factor(baseInt, primeFactors);
			vector<int> outFactors, inFactors;
			for (unsigned int i = 0; i < primeFactors.size(); i++)
			{
				if (primeFactors[i] == primeFactors[i + root - 1])
				{
					outFactors.push_back(primeFactors[i]);
					i += root - 1;
				}
				else
				{
					inFactors.push_back(primeFactors[i]);
				}
			}
			int outProduct = 1;
			int inProduct = 1;
			for (int i = 0; i < outFactors.size(); i++)
			{
				outProduct *= outFactors[i];
			}
			for (int i = 0; i < inFactors.size(); i++)
			{
				inProduct *= inFactors[i];
			}
			Number* out = new Basic(outProduct);
			if (inProduct == 1)
			{
				//delete n;
				//delete this;
				return out;
			}
			else
			{
				Number* in = new Basic(outProduct);
				//Exponent answer = new Exponent(out, in, n);  //need exponent

			}
		}
		//Number* den = new Basic(n->getDen()->getValue());   //do first because n will be deleted
		//Number* base = expo(n->getNum());
		//Number* one = new Basic(1);
		//Number* power = new Fraction(one, den);
		//Number* answer = new Exponent(base, power);    //need exponent class
		//return answer;
	}
	return n;   //needs return statement outside if
}

*/




