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

vector<char> shunt(string expression)
{

	vector<char> input;
	vector<char> output;
	vector<char> stack;

	//Precedence
	int leftper = 1;
	int log = 2;
	int exp = 2;
	int mult = 3;
	int div = 3;
	int sub = 4;
	int add = 4;

	int stringSize = expression.size();

	//Turn string input into vector
	for(int i = 0; i < stringSize; i++)
	{
		input.push_back(expression[i]);
	}

	for(int i = 0; (unsigned int)i < input.size(); i++)
	{
		if (input[i] == ' ')
		{
			output.push_back(' ');
		}
		if (isdigit(input[i]))
		{
			output.push_back(input[i]);
		}
		if(input[i] == '+'||input[i] == '-'||input[i] == '*'||input[i] == '/'||input[i] == '^')
		{

		}
		if (input[i] == '(')
		{
			stack.push_back(input[i]);
		}
		if (input[i] == ')')
		{
			while(stack.back() != '(')
			{
				output.push_back(stack.back());
				stack.pop_back();
			}
			if(stack.back() == '(')
			{
				stack.pop_back();
			}
			if(stack.back() == '+'||stack.back() == '-'||stack.back() == '*'||stack.back() == '/'||stack.back() == '^')
			{
				output.push_back(stack.back());
				stack.pop_back();
			}
		}
	}


	return output;

}

void printVectorChar(vector<char> toPrint)
{
	ostringstream stream;

	for(int i = 0; (unsigned int)i < toPrint.size(); i++)
	{
		stream << toPrint[i];
	}

	string out = stream.str();
	cout << out;
}

int main()
{
	string in = "(1 1 1)";
	vector<char> test;
	test = shunt(in);
	printVectorChar(test);

	return 0;

}

