/*
 * main.cpp
 *
 *  Created on: Apr 6, 2014
 *      Author: Nikita
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void printVectorChar(vector<char> toPrint)
{
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
	vector<char> error;
	string ERROR = "ERROR";
	string erSqrt = ": You did not input the square root operator correctly!";
	string erLog = ": You did not input the log operator correctly!";
	string erPer = ": Unbalanced parentheses!";
	int j = 0;

	stack.push_back(' '); //initialize stack, otherwise program crash if the expression does not start with '('

	for(int i = 0; (unsigned int)i < ERROR.size(); i++)
	{
			error.push_back(ERROR[i]);
	}



	//Precedence of operations
	int precedenceIn = 0;
	int precedenceSt = 0;
	int logpre = 3;
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
		bool sqrt = false;
		bool pi = false;
		bool log = false;
		bool nrt = false;

		cout<< endl<< j;
		j++;
		cout<<endl<<"Input["<<i<<"]: "<<input[i];
		cout<< endl<< "stack: ";
		printVectorChar(stack);
		cout<< endl << "output: ";
		printVectorChar(output);

		//check for sqrt:n
		if(input[i] == 's')
		{
			if(input[i+1] == 'q'&&input[i+2] == 'r'&&input[i+3] == 't'&&input[i+4]==':')
			{
				sqrt = true;
			}
			else
			{
				for(int i = 0; (unsigned int)i < erSqrt.size(); i++)
				{
						error.push_back(erSqrt[i]);
				}
				return error;
			}
		}

		//check for log
		if(input[i] == 'l')
		{																	//base is a digit/e/pi
			if(input[i+1] == 'o'&&input[i+2] == 'g'&&input[i+3] == '_'&&(isdigit(input[i+4])||input[i+4] == 'e'||(input[i+4] == 'p'&&input[i+5] == 'i'))&&(input[i+5] == ':'||input[i+6] == ':'))
			{
				if(input[i+4] == 'p'&&input[i+5] == 'i')	//Log has base pi
					pi = true;
				log = true;
			}
			else
			{
				for(int i = 0; (unsigned int)i < erLog.size(); i++)
				{
						error.push_back(erLog[i]);
				}
				return error;
			}
		}

		//check for nrt
		if(isdigit(input[i])&&input[i+1] == 'r'&&input[i+2] == 't'&&input[i+3] == ':')
			nrt = true;

		//Put a space in the output stack
		if (input[i] == ' '&& output.back()!= ' ')
		{
			output.push_back(input[i]);
		}

		//Put the digit in the output stack
		else if ((isdigit(input[i])||input[i] == 'e' || (input[i] == 'p'&&input[i+1] == 'i'))&&!nrt)
		{
			output.push_back(input[i]);
			if(input[i] == 'p'&&input[i+1] == 'i')
			{
				output.push_back(input[i+1]);
				pi = true;
			}
		}

		//If an operator
		else if(input[i] == '+'||input[i] == '-'||input[i] == '*'||input[i] == '/'||input[i] == '^'||input[i] == 'l'||sqrt||log||nrt)
		{
			//No operators on the stack
			if(stack.back() == ' ')
			{
				//sqrt
				if(sqrt)
				{
					stack.push_back('s');
				}
				else if(log)
				{
					stack.push_back('l');
					stack.push_back('b');
					//base
					if(pi)
					{
						stack.push_back('p');
					}
					else
						stack.push_back(input[i+4]);
				}
				else if(nrt)
				{
					stack.push_back(input[i]); //n
					stack.push_back('r');
					stack.push_back('t');
				}
				else
				stack.push_back(input[i]);
			}

			//There is a operator on the stack
			else
			{
				//Precedence of the input
				switch(input[i]){
				case '+': precedenceIn = add;	break;
				case '-': precedenceIn = sub; 	break;
				case '*': precedenceIn = mult;	break;
				case '/': precedenceIn = div; 	break;
				case '^': precedenceIn = exp; 	break;
				case 's': if(sqrt){precedenceIn = exp;} break;
				case 'l': if(log){precedenceIn = logpre;} 	break;
				default: precedenceIn = 0;		break;}
				if(input[i+1] == 'r') //nrt cant be checked above
					precedenceIn = exp;
				//Precedence comparing to
				switch(stack.back()){
				case '+': precedenceSt = add;	break;
				case '-': precedenceSt = sub;	break;
				case '*': precedenceSt = mult;	break;
				case '/': precedenceSt = div;	break;
				case '^': precedenceSt = exp;	break;
				case 's': precedenceSt = exp;   break;
				default: precedenceSt = 0;		break;}
				//check if log and nrt in stack since it cant be checked in the switch
				if(stack[stack.size()-3] == 'l')
					precedenceSt = logpre;
				if(stack[stack.size()-2] == 'r')
					precedenceSt = exp;

				cout<<endl<<"Pin: "<<precedenceIn<<" Pst: "<<precedenceSt;

				//Input is of higher or equal precendence
				if(precedenceIn > precedenceSt)
				{
					if(log)
					{
						stack.push_back('l');
						stack.push_back('b');
						//base
						if(pi)
						{
							stack.push_back('p');
						}
						else
							stack.push_back(input[i+4]);
					}
					else if(nrt)
					{
						stack.push_back(input[i]);
						stack.push_back('r');
						stack.push_back('t');
					}
					else
						stack.push_back(input[i]); //Just put it on top of what is there
				}
				//Input is of lesser precedence
				else{
					while(precedenceIn <= precedenceSt)
					{
						if(output.back() != ' ')
							output.push_back(' ');	//formatting
						if(stack[stack.size()-3] == 'l'||stack[stack.size()-2] == 'r')	// log or nrt
						{
							int k = 0;
							while(k < 3)
							{
								output.push_back(stack[stack.size()-3+k]);
								k++;
							}
							k = 0;
							while(k < 3)	// Cant be done in the same while loop since we still need the information being popped
							{
								stack.pop_back();
								k++;
							}
						}
						else
						{
						output.push_back(stack.back());
						stack.pop_back();
						}

						switch(stack.back()){
						case '+': precedenceSt = add;	break;
						case '-': precedenceSt = sub;	break;
						case '*': precedenceSt = mult; 	break;
						case '/': precedenceSt = div;	break;
						case '^': precedenceSt = exp; 	break;
						case 's': precedenceSt = exp;	break;
						default: precedenceSt = 0; 		break;}
						//check if log in stack since it cant be checked in the switch
						if(stack[stack.size()-3] == 'l')
							precedenceSt = logpre;
						if(stack[stack.size()]-2 == 'r')
							precedenceSt = exp;
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
			else if(stack.back() == '+'||stack.back() == '-'||stack.back() == '*'||stack.back() == '/'||stack.back() == '^'||stack.back() == 's'||stack[stack.size()-3]=='l')
			{
				if(stack[stack.size()-3] == 'l')
				{
					int k = 0;
					while(k < 3)
					{
						output.push_back(stack[stack.size()-3+k]);
						k++;
					}
					k = 0;
					while(k < 3)	// Can't be done in the same while loop since we still need the information being popped
					{
						stack.pop_back();
						k++;
					}
				}
				else
				{
				output.push_back(' ');
				output.push_back(stack.back());
				stack.pop_back();
				}
			}
		}
		cout<<endl<<sqrt<<pi<<log<<nrt;
		if(sqrt)
			i = i+4; //move 4 spaces over since sqrt is taken care of
		if(pi)
			i++;
		if(log)
			i = i+5;
		if(nrt)
			 i = i+3;

	}

	int size = stack.size();
	for(int i = 0; i < size; i++)
	{
		if(stack[stack.size()-3] == 'l')	// log
		{
			output.push_back(' ');
			int k = 0;
			while(k < 3)
			{
				output.push_back(stack[stack.size()-3+k]);
				k++;
			}
			k = 0;
			while(k < 3)	// Cant be done in the same while loop since we still need the information being popped
			{
				stack.pop_back();
				k++;
			}
		}
		else if(stack[stack.size()-2] == 'r')	//nrt
		{
			cout<<"test";
			output.push_back(' ');
			int k = 0;
			while(k < 3)
			{
				output.push_back(stack[stack.size()-3+k]);
				k++;
			}
			k = 0;
			while(k < 3)	// Cant be done in the same while loop since we still need the information being popped
			{
				stack.pop_back();
				k++;
			}
		}
		else
		{
		output.push_back(' ');
		output.push_back(stack.back());
		stack.pop_back();
		}
	}

	for(int i = 0; (unsigned int)i < output.size(); i++)
	{
		if(output[i] == '(' || output[i] == ')')
		{
			for(int i = 0; (unsigned int)i < erPer.size(); i++)
			{
					error.push_back(erPer[i]);
			}
			return error;
		}
	}


	return output;
}



int main()
{
	string in = "(1 + sqrt:25) / 2 + 4rt:16 + log_2:3 * 3rt:3";
	vector<char> test;
	test = shunt(in);
	cout<<endl<<endl<<"Input:  "<<in<<endl;
	cout<<"Final:  ";
	printVectorChar(test);

	/*
	cout<<"If this is your first time using this calculator please check out \"Help\""<<endl;
	while(true)
	{
		string in;
		vector<char> test;
		int selection = 0;
		cout<<endl<<"1. Input your expression"<<
		endl<<"2. Past results and set ANS"<<
		endl<<"3. Help"<<
		endl<<"0. Quit"<<
		endl<<endl<<"Input your selection: ";
		cin >> selection;

		switch(selection){
		case 1: cout<<"Input your expression: ";
						//cin.getline(in, in.size());
						test = shunt(in);
						cout<<endl<<endl<<"Input:  "<<in<<endl;
						cout<<"Final:  ";
						printVectorChar(test);break;
		case 2: cout<<"Under construction!"; break;//memory()
		case 3: cout<<"Under construction!"; break;//help()
		case 0: cout<<endl<<"Good bye!"; return 0;
		default: cout<<"You did not input a valid selection!"; break;



		}

	}*/

	return 0;

}
