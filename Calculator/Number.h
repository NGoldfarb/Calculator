/*
 * Number.h
 *
 *  Created on: Apr 6, 2014
 *      Author: Nikita
 */

#ifndef NUMBER_H_
#define NUMBER_H_

#include <string>
using namespace std;

class Number
{

public:

	string type;

	//When I try to set it to return Number it says that it must implement the function?
	virtual Number add()=0;	//example
	virtual void subtract()=0;
	virtual void multiply()=0;
	virtual void divide()=0;
	virtual void exponentiate()=0;
	virtual void log()=0;

	virtual Number();
	virtual ~Number();

};



#endif /* NUMBER_H_ */
