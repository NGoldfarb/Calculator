/*
 * main.cpp
 *
 *  Created on: Apr 6, 2014
 *      Author: Nikita
 */
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#
using namespace std;

void printVectorChar(vector<char> toPrint)
{
	ostringstream stream;

	for(int i = 0; (unsigned int)i < toPrint.size(); i++)
	{
		cout<< toPrint[i];
	}
}


vector<char> shunt(string expression)
{
	//Algorithm on http://en.wikipedia.org/wiki/Shunting-yard_algorithm used for reference

	vector<char> input;
	vector<char> output;
	vector<char> stack;
	stack.push_back(' '); //initialize stack, otherwise program crash if the expression does not start with '('

	//Precedence of operations
	int precedenceIn = 0;
	int precedenceSt = 0;
	int leftper = 4;
	int log = 3;
	int exp = 3;
	int mult = 2;
	int div = 2;
	int sub = 1;
	int add = 1;

	int stringSize = expression.size();

	//Turn string input into vector
	for(int i = 0; i < stringSize; i++)
	{
		input.push_back(expression[i]);
	}

	for(int i = 0; (unsigned int)i < input.size(); i++)
	{
		cout<< endl<< i;
		cout<< endl<< "stack: ";
		printVectorChar(stack);
		cout<< endl << "output: ";
		printVectorChar(output);

		//Put a space in the output stack
		if (input[i] == ' '&& output.back()!= ' ')
		{
			output.push_back(input[i]);
		}

		//Put the digit in the output stack
		else if (isdigit(input[i]))
		{
			output.push_back(input[i]);
		}

		//If an operator
		else if(input[i] == '+'||input[i] == '-'||input[i] == '*'||input[i] == '/'||input[i] == '^')
		{
			//No operators on the stack
			if(stack.back() != '+'&&stack.back() != '-'&&stack.back() != '*'&&stack.back() != '/'&&stack.back() != '^')
			{
				stack.push_back(input[i]);
			}

			//There is a operator on the stack
			else
			{
				cout<<"test: "<<input[i];
				//Precedence of the input
				switch(input[i]){
				case '+': precedenceIn = add;	break;
				case '-': precedenceIn = sub; 	break;
				case '*': precedenceIn = mult;	break;
				case '/': precedenceIn = div; 	break;
				case '^': precedenceIn = exp; 	break;
				default: precedenceIn = 0;		break;}
				//Precedence comparing to
				switch(stack.back()){
				case '+': precedenceSt = add;	break;
				case '-': precedenceSt = sub;	break;
				case '*': precedenceSt = mult;	break;
				case '/': precedenceSt = div;	break;
				case '^': precedenceSt = exp;	break;
				default: precedenceSt = 0;		break;}

				cout<< endl<< "PIn: "<< precedenceIn<<" PSt: "<<precedenceSt;

				//Input is of higher or equal precendence
				if(precedenceIn > precedenceSt)
				{
					stack.push_back(input[i]); //Just put it on top of what is there
				}
				//Input is of lesser precedence
				else{
					while(precedenceIn <= precedenceSt)
					{
						output.push_back(stack.back());
						stack.pop_back();

						switch(stack.back()){
						case '+': precedenceSt = add;	break;
						case '-': precedenceSt = sub;	break;
						case '*': precedenceSt = mult; 	break;
						case '/': precedenceSt = div;	break;
						case '^': precedenceSt = exp; 	break;
						default: precedenceSt = 0; 		break;}
					}
					stack.push_back(input[i]);
				}
			}
		}

		//Input is a left peren
		else if (input[i] == '(')
		{
			stack.push_back(input[i]);
		}

		//Input is a right peren
		else if (input[i] == ')')
		{
			while(stack.back() != '(')
			{
				output.push_back(' ');
				output.push_back(stack.back());
				stack.pop_back();
			}
			if(stack.back() == '(')
			{
				stack.pop_back();
			}
			else if(stack.back() == '+'||stack.back() == '-'||stack.back() == '*'||stack.back() == '/'||stack.back() == '^')
			{
				output.push_back(' ');
				output.push_back(stack.back());
				stack.pop_back();
			}
		}
	}

	int size = stack.size();
	for(int i = 0; i < size; i++)
	{
		output.push_back(' ');
		output.push_back(stack.back());
		stack.pop_back();
	}
	return output;

}



int main()
{
	string in = "1 - (3 + 2) ^ 3 / 5 + 3";
	vector<char> test;
	test = shunt(in);
	cout<<endl<<"Input:  "<<in<<endl;

	cout<<"Final:  ";
	printVectorChar(test);

	return 0;

}

