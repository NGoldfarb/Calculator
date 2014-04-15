#ifndef EXPONENT_H
#define EXPONENT_H

#include <string>
#include <iostream>
#include "Number.h"
#include "Basic.h"

using namespace std;

class Exponent :public Number{
public:      //coef   base      degree
	Exponent(Number*, Number*, Number*);
	~Exponent();


	string type;
	Number* add(Number*);
	Number* subtract(Number*);
	Number* multiply(Number*);
	Number* divide(Number*);
	int getValue();
	char getCharValue();
	Number* simplifyHelper();
	Number* expo(Number*);
	string getType();
	void print();
	Number* getNum();
	Number* getDen();
	void setNum(Number*);
	void setDen(Number*);
	void factor(int, vector<int>&);
	void factorHelper(int, vector<int>&);
	bool isPrime(int);
	Number* simplify(Number*, int);
	//Number* negExpo(Number*);
	//Number* expon(Number*);
	//for irrational class
	Number* getCoef();
	Number* getExp();
	Number* getBase();

	Number* base;
	Number* exp;
	Number* coef;

	//for expression
	vector<Number*> getVect();

	void simplify();
	void setValue(int);
	Number* log(Number*);
};







#endif /* EXPONENT_H */
