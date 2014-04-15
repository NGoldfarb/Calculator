#include "Basic.h"
#include "Exponent.h"
#include "Expression.h"
#include <stdexcept>

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
    else if(n->getType() == "Fraction")
    {
    	Number* x = new Basic(n->getNum()->getValue() + value*n->getDen()->getValue());
    	Number* y = new Basic(n->getDen()->getValue());
    	Number* z = new Fraction(x, y);
    	delete n;
    	delete this;
    	return z;
    }
    else if(n->getType() == "irrational")
    {
    	Basic* duplicate = new Basic(value);
    	vector<Number*> exp;
    	exp.push_back(duplicate);
    	exp.push_back(n);
    	Number* answer = new Expression(exp);
    	delete this;
    	return answer;
    }
    else
    {
    	throw invalid_argument("Currently, you may not add/subtract anything other than integers and fractions to integers.");
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
    else if(n->getType() == "Fraction")
    {
    	Basic* x = new Basic(value*n->getNum()->getValue());
    	Basic* y = new Basic(n->getDen()->getValue());  //created another Basic that won't get destructed when n does;
    	Fraction* z = new Fraction(x, y);
    	delete n;
    	delete this;
    	z->simplify();
    	return z;
    }
    else
    {
    	throw invalid_argument("Currently, you may not multiply integers by anything other than fractions or integers.");
    }
}

Number* Basic::divide(Number* n)
{
    if(n->getType() == "Basic")
    {
    	if(n->getValue() == 0)
    	{
    		throw invalid_argument("You can't divide by zero!");
    	}
    	else if (value%n->getValue() == 0)
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
    else
    {
    	throw invalid_argument("Currently, you may not divide integers by anything other than integers or fractions.");
    }
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
    	if(n->getNum()->getValue() != 1)
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
    		for(unsigned int i = 0 ; i < primeFactors.size(); i++)
    		{
    			if(primeFactors[i] == primeFactors[i+root-1])
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
    		for(unsigned int i = 0; i < outFactors.size(); i++)
    		{
    			outProduct *= outFactors[i];
    		}
    		for(unsigned int i = 0; i < inFactors.size(); i++)
    		{
    			inProduct *= inFactors[i];
    		}
    		Number* out = new Basic(outProduct);
    		if(inProduct == 1)
    		{
    			//delete n;
    			//delete this;
    			return out;
    		}
    		else
    		{
    			Number* in = new Basic(outProduct);
    			Number* answer = new Exponent(out, in, n);  //need exponent
    			return answer;

    		}
    	}
    	//Number* den = new Basic(n->getDen()->getValue());   //do first because n will be deleted
    	//Number* base = expo(n->getNum());
    	//Number* one = new Basic(1);
    	//Number* power = new Fraction(one, den);
    	//Number* answer = new Exponent(base, power);    //need exponent class
    	//return answer;
    }
    else
    {
    	throw invalid_argument("That operation is currently not supported.");
    }
}
Number* Basic::negExpo(Number* n)
{
	Number* num = new Basic(1);
	n->setValue(n->getValue() * (-1));
	Number* answer = num->divide(expo(n));
	return answer;
}

void Basic::factor(int num, vector<int>& primeFactors)  //at end, primeFactors contains prime factors of num in ascending order
{
	primeFactors.clear();
	return factorHelper(num, primeFactors);
}
void Basic::factorHelper(int num, vector<int>& primeFactors)
{
	if(isPrime(num))
	{
		primeFactors.push_back(num);
	}
	else
	{
		int i = 2;
		while(!isPrime(i) || num%i != 0)
		{
			i++;
		}
		primeFactors.push_back(i);
		factorHelper(num/i, primeFactors);
	}
}
bool Basic::isPrime(int num)
{
	double squareRoot = sqrt(num);
	for(int i = 2; i <= squareRoot; i++)
	{
		if (num%i == 0)
		{
			return false;
		}
	}
	return true;
}

Number* Basic::log(Number* arg)   //works when base and argument are both basic, answer is basic
{
	if(arg->getType() == "Basic")
	{
		int argument = arg->getValue();
		int counter = 0;
		while(argument%value == 0 && argument != 1)
		{
			counter++;
			argument /= value;
		}
		if(argument == 1)
		{
			Basic* answer = new Basic(counter);
			delete arg;
			delete this;
			return answer;
		}
		else
		{
			throw invalid_argument("Logs that do not simplify to integers are currently not supported");
		}
	}
	else
	{
		throw invalid_argument("Logs that do not simplify to integers are currently not supported");
	}
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
vector<Number*> Basic::getVect()
{
	vector<Number*> answer;
	return answer;
}
Number* Basic::simplifyHelper()
{
	return this;
}


