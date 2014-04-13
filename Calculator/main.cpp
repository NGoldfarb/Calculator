/*
 * main.cpp
 *
 *  Created on: Apr 6, 2014
 *      Author: Nikita
 */
#include <iostream>
#include <vector>
#include <string>
#include "Number.h"
#include "Basic.h"
#include "Fraction.h"
#include <stdexcept>
using namespace std;

void printVectorChar(vector<char> toPrint)
{
	for(int i = 0; (unsigned int)i < toPrint.size(); i++)
	{
		cout<< toPrint[i];
	}
}


vector<char> shunt(string expression, bool debug)
{
	//Algorithm on http://en.wikipedia.org/wiki/Shunting-yard_algorithm used for reference

	vector<char> input;
	vector<char> output;
	vector<char> stack;
	int j = 0;

	stack.push_back(' '); //initialize stack, otherwise program crash if the expression does not start with '('

	//Precedence of operations
	int precedenceIn = 0;
	int precedenceSt = 0;
	int logpre = 3;
	int exp = 3;
	int mult = 2;
	int div = 2;//asdfa
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
		bool neg = false;
		bool ans = false;

		if(debug)
		cout<< endl<< j;
		j++;

		if(debug)
		{
		cout<<endl<<"Input["<<i<<"]: "<<input[i];
		cout<< endl<< "stack: ";
		printVectorChar(stack);
		cout<< endl << "output: ";
		printVectorChar(output);
		}

		//check if valid, there's probably a more eye pleasing way to do this..
		if(!isdigit(input[i])&&input[i] != '+'&&input[i] != '-'&&input[i] != '*'&&input[i] != '/'
				&&input[i] != 's'&&input[i] != 'q'&&input[i] != 'r'&&input[i] != 't'&&input[i] != 'l'
						&&input[i] != 'o'&&input[i] != 'g'&&input[i] != '_'&&input[i] != ':'&&input[i] != '^'
								&&input[i] != 'r'&&input[i] != 't'&&input[i] != ' '&&input[i] != '('&&input[i] != ')'
										&&input[i] != 'p'&&input[i] != 'i'&&input[i] != 'e'&&input[i] != 'a'&&input[i] != 'n')
		{
			throw invalid_argument("You entered an invalid character!");
		}

		//check if starting with a space
		if(input[i] == ' '&&output.size() == 0)
		{
			throw invalid_argument("Don't start the expression with a space!");
		}

		//check for negative number
		if(input[i] == '-'&&(isdigit(input[i+1])||input[i+1] == 'p'||input[i+1] == 'e'))
		{
			neg = true;
		}

		//check for ans
		if(input[i] == 'a')
		{
			if(input[i+1] == 'n'&&input[i+2] == 's')
				ans = true;
			else
				throw invalid_argument("You did not input ans correctly!");
		}

		//check for sqrt:n
		if(input[i] == 's')
		{
			if(input[i+1] == 'q'&&input[i+2] == 'r'&&input[i+3] == 't'&&input[i+4]==':')
			{
				sqrt = true;
			}
			else
			{	//sqrt not input properly
				throw invalid_argument("You did not input the square root operator correctly! Input as sqrt:n!");
			}
			//check for negative number
			if(input[i+5] == '-')
			{
				throw invalid_argument("You can't take the square root of a negative number!");
			}
		}

		//check for log
		if(input[i] == 'l')
		{
			if(input[i+1] == 'o'&&input[i+2] == 'g'&&input[i+3] == '_')
			{
				log = true;
			}
			else
			{	//log not input properly
				throw invalid_argument("You can't take the square root of a negative number!");
			}
		}

		//check for pi
		if(input[i] == 'p')
		{
			if(input[i+1] != 'i')
			{
				throw invalid_argument("Enter pi as pi and not p!");
			}
			else if(input[i+2] == 'r'&&input[i+3] == 't') //Check to see if being used in nrt
			{
				throw invalid_argument("That is not valid n for nrt! Integers only!");
			}
			else
				pi = true;
		}


		//check for a lone i
		if(input[i] == 'i')
		{
			throw invalid_argument("No complex numbers!");
		}

		//check for nrt, if n is negative increase index checked by one
		if(input[i+1+(int)neg] == 'r'&&input[i+2+(int)neg] == 't'&&input[i+3+(int)neg] == ':')
		{
			if(!isdigit(input[i+(int)neg]))
			{
				throw invalid_argument("That is not valid n for nrt! Integers only!");
			}
			else
			nrt = true;
		}


		//Put a space in the output stack
		if ((input[i] == ' '||input[i] == ':')&&output.back()!= ' ')
		{
			//Check for double spaces
			if(input[i-1] == ' '||input[i+1] == ' ')
			{
				throw invalid_argument("Don't enter two spaces in a row!");
			}
			else
			output.push_back(' ');
		}

		//Put the digit in the output stack
		else if ((isdigit(input[i])||input[i] == 'e'||input[i] == 'p'||(input[i] == '-'&&neg)||input[i] == 'a')&& !nrt)
		{
			if(input[i] == 'p')
			{
				if(input[i+1] == 'i')
				{
				output.push_back(input[i]);
				output.push_back(input[i+1]);
				pi = true;
				}
				else
				{
					throw invalid_argument("Enter pi as pi and not p!");
				}
			}
			else{
				output.push_back(input[i]);}
		}

		//If an operator
		else if(input[i] == '+'||((input[i] == '-')&& !neg)||input[i] == '*'||input[i] == '/'||input[i] == '^'||input[i] == 'l'||sqrt||log||nrt)
		{

			//Check for spaces before and after an operator
			if((input[i-1] != ' '||input[i+1] != ' ')&&!neg&&!nrt&&!sqrt)
			{
				throw invalid_argument("You need a space infront and behind an operator!");
			}
			//No operators on the stack
			if(stack.back() == ' ')
			{
				if(sqrt)
				{
					stack.push_back('s');
				}
				else if(log)
				{
					stack.push_back('l');
					stack.push_back('b');
				}
				else if(nrt)
				{
					if(input[i] == '-')
						stack.push_back('n');
					else
						stack.push_back(input[i]); //n
					if(neg)
						stack.push_back(input[i+1]);
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
				if(input[i+1+neg] == 'r') //nrt cant be checked above
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
				if(stack[stack.size()-2] == 'l')
					precedenceSt = logpre;
				if(stack[stack.size()-2] == 'r')
					precedenceSt = exp;

				if(debug)
				cout<<endl<<"Pin: "<<precedenceIn<<" Pst: "<<precedenceSt;

				//Input is of higher or equal precendence
				if(precedenceIn > precedenceSt)
				{
					if(log)
					{
						stack.push_back('l');
						stack.push_back('b');
					}
					else if(nrt)
					{
						if(input[i] == '-')
							stack.push_back('n');
						else
							stack.push_back(input[i]);
						if(neg)
							stack.push_back(input[i+1]);
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
						if(stack[stack.size()-2] == 'r')	//nrt
						{
							int k = 0;
							while(k < 3 + neg)
							{
								output.push_back(stack[stack.size()-(3+neg)+k]);
								k++;
							}
							k = 0;
							while(k < 3 + neg)	// Cant be done in the same while loop since we still need the information being popped
							{
								stack.pop_back();
								k++;
							}
						}
						else if(stack[stack.size()-2] == 'l')
						{
							int k = 0;
							while(k < 2)
							{
								output.push_back(stack[stack.size()-2+k]);
								k++;
							}
							k = 0;
							while(k < 2)	// Cant be done in the same while loop since we still need the information being popped
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
						//case '(': precedenceSt = peren; break;
						default: precedenceSt = 0; 		break;}
						//check if log in stack since it cant be checked in the switch
						if(stack[stack.size()-2] == 'l')
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
				if(stack[stack.size()-2] == 'l')
				{
					int k = 0;
					while(k < 2)
					{
						output.push_back(stack[stack.size()-2+k]);
						k++;
					}
					k = 0;
					while(k < 2)	// Can't be done in the same while loop since we still need the information being popped
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
		if(debug)
		cout<<endl<<sqrt<<pi<<log<<nrt<<neg;
		if(sqrt)
			i = i+4; //move 4 spaces over since sqrt is taken care of
		if(pi)
			i++;
		if(log)
			i = i+3;
		if(ans)
			i = i+2;
		if(nrt)
		{
			if(neg)
				i = i+4;
			else
				i = i+3;
		}

	}

	//everything is done, put what's left on the stack on the output
	int size = stack.size();
	for(int i = 0; i < size; i++)
	{
		if(stack[stack.size()-2] == 'l')	// log
		{
			output.push_back(' ');
			int k = 0;
			while(k < 2)
			{
				output.push_back(stack[stack.size()-2+k]);
				k++;
			}
			k = 0;
			while(k < 2)	// Cant be done in the same while loop since we still need the information being popped
			{
				stack.pop_back();
				k++;
			}
		}
		else if(stack[stack.size()-2] == 'r')	//nrt
		{
			bool neg = false;
			if(stack[stack.size()-4] == 'n')
				neg = true;
			output.push_back(' ');
			int k = 0;
			while(k < 3 + (int)neg)
			{
				if(stack[stack.size()-(3+neg)+k] == 'n')
					output.push_back('-');
				else
					output.push_back(stack[stack.size()-(3+neg)+k]);
				k++;
			}
			k = 0;
			while(k < 3 + (int)neg)	// Cant be done in the same while loop since we still need the information being popped
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

	//Unbalanced parentheses
	for(int i = 0; (unsigned int)i < output.size(); i++)
	{
		if(output[i] == '(' || output[i] == ')')
		{
			throw invalid_argument("Unbalanced parentheses!");
		}
	}


	return output;
}

void printNumberStack(vector<Number*> stack)
{
	cout<<"Numbers in stack: ";
	for(unsigned int i = 0; i < stack.size(); i++)
	{
		stack[i]->print();
		cout << " ";
	}
}

Number* evalShunt(vector<char> expression, bool debug)
{
    vector<Number*> stack;
    int i = 0;
    while ((unsigned int)i < expression.size())
    {  //need to initialize basics or irrationals to numbers
        if ('0' <= expression[i] && expression[i] <= '9' && expression[i + 1] != 'r')  //if next token is digit and not root
        {
            int num = 0;
            int multiplier = 1;  //multiplier for powers of 10
            int counter = 1;   //counts digits
            while (expression[i+1] != ' ')  //determines how many digits the number is
            {
                multiplier *= 10;
                counter++;
                i++;
            }
            i -= (counter - 1);
            while(expression[i] != ' ')   //forms multidigit number
            {
            	num += (expression[i] - '0') * multiplier;
            	multiplier /= 10;
            	i++;
            }
            Number* basic = new Basic(num);
            stack.push_back(basic);
            i++;
        }
        else if (expression[i] == 'e')  //if next token is e
        {
            /*Number* y = new Basic(1);
            Number* e = new Irrational('e',y,y);   //update when irrational constructor known
            stack.push_back(e);
            i += 2;*/
        }
        else if (expression[i] == 'p')  //if next token is pi
        {
            /* y = new Basic(1);
            Number* pi = new Irrational('p', y, y);  //assuming irrational(isPi)
            stack.push_back(pi);
            i += 3;*/
        }
        else if (expression[i] == ' ') //next token is space, increment i
        {
            i++;
        }
        else  //next token is operator or error
        {
            if (expression[i] == '+')  //perform addition on top two Numbers on stack
            {
                if (stack.size() < 2)  //make sure there is enough on the stack
                {
                    throw invalid_argument("The addition does not have 2 operands.");
                }
                else
                {
                    Number* num1 = stack.back();
                    stack.pop_back();
                    Number* num2 = stack.back();
                    stack.pop_back();
                    Number* num3 = num1->add(num2);
                    stack.push_back(num3);
                    i += 2;
                }
            }
            else if (expression[i] == '-')  //perform subtraction on top two Numbers on stack
            {
                if (stack.size() < 2)  //make sure there is enough on the stack
                {
                    throw invalid_argument("The subtraction does not have 2 operands.");
                }
                else
                {
                    Number* num1 = stack.back();
                    stack.pop_back();
                    Number* num2 = stack.back();
                    stack.pop_back();
                    Number* num3 = num2->subtract(num1);
                    stack.push_back(num3);
                    i += 2;
                }
            }
            else if (expression[i] == '*')  //perform multiplication on top two Numbers on stack
            {
                if (stack.size() < 2)  //make sure there is enough on the stack
                {
                    throw invalid_argument("The multiplication does not have 2 operands.");
                }
                else
                {
                    Number* num1 = stack.back();
                    stack.pop_back();
                    Number* num2 = stack.back();
                    stack.pop_back();
                    Number* num3 = num1->multiply(num2);
                    stack.push_back(num3);
                    i += 2;
                }
            }
            else if (expression[i] == '/')  //perform division on top two Numbers on stack
            {
                if (stack.size() < 2)  //make sure there is enough on the stack
                {
                    throw invalid_argument("The division does not have 2 operands.");
                }
                else
                {
                    Number* num1 = stack.back();
                    stack.pop_back();
                    Number* num2 = stack.back();
                    stack.pop_back();
                    Number* num3 = num2->divide(num1);
                    stack.push_back(num3);
                    i += 2;
                }
            }
            else if (expression[i] == '^')  //perform exponentiation on top two Numbers on stack
            {
                if (stack.size() < 2)  //make sure there is enough on the stack
                {
                    throw invalid_argument("The exponent does not have 2 operands.");
                }
                else
                {
                    Number* num1 = stack.back();
                    stack.pop_back();
                    Number* num2 = stack.back();
                    stack.pop_back();
                    Number* num3 = num1->expo(num2);
                    stack.push_back(num3);
                    i += 2;
                }
            }
            else if (expression[i] == 'l')  //performs logarithm on top two Numbers of stack
            {
                if (stack.size() < 2)  //make sure there is enough on the stack
                {
                    throw invalid_argument("The logarithm does not have 2 operands.");
                }
                else
                {
                    Number* num1 = stack.back();
                    stack.pop_back();
                    Number* num2 = stack.back();
                    stack.pop_back();
                    Number* num3 = num2->expo(num1);  //assuming for base.log(argument) CHANGE EXP TO LOG
                    stack.push_back(num3);
                    i += 3;  //based on log_x:y being x y lb
                }
            }
            else if (expression[i] == 's')
            {
                if (stack.size() < 1)
                {
                    throw invalid_argument("There is nothing to take the square root of.");
                }
                else
                {
                    Number* num1 = stack.back();
                    stack.pop_back();
                    Number* a1 = new Basic(1);
                    Number* a2 = new Basic(2);
                    Number* half = new Fraction(a1, a2);  //assuming Fraction(Number* num, Number* denom)
                    Number* num2 = num1->expo(half);
                    delete num1;
                    delete half;
                    stack.push_back(num2);
                    i += 2;
                }
            }
            else if ('0' <= expression[i]&&expression[i] <= '9') //must be nth root, can only take single digits
            {
                if (stack.size() < 1)
                {
                    throw invalid_argument("There is nothing to take nth root of.");
                }
                else
                {
                    int root = expression[i] - '0';
                    Number* a1 = new Basic(root);
                    Number* a2 = new Basic(1);
                    Number* frac = new Fraction(a2, a1);


                    Number* num1 = stack.back();
                    stack.pop_back();
                    Number* num2 = num1->expo(frac);
                    delete num1;

                    stack.push_back(num2);
                    i += 4;
                }
            }
            else  //maybe Nikita took care of this
            {
                //throw exception("Something's messed up.");
            }

        }
        if(debug)
        {
        printNumberStack(stack);
        cout << endl;
        }
    }
    return stack[0];
}

/*void memory(vector<Number> memory, int &ans)
{

}*/

void help()
{
	char selection;
	while(true)
	{
	cout<<endl<<"What do you need help with?";
	cout<<endl<<"1. Operators"
		<<endl<<"2. Square root"
		<<endl<<"3. N root"
		<<endl<<"4. Logarithms"
		<<endl<<"5. Examples"
		<<endl<<"0. Quit";

	cout<<endl<<endl<<"Input your selection: ";
	cout<<endl;

	cin>>selection;
	cin.ignore();

	switch(selection)
	{
	case '1': cout<<"When using operators, such as + - * / ^ make sure to put a space between the operator"
			" and the numbers being operated on, parentheses do not need spaces."
			<<endl<<"Example: 1 + 2 or (4 / 2)"<<endl;	break;

	case '2': cout<<"To take the square root of a number input sqrt:n where n is the number you"
			" want to take the square root of."<<endl<<"Example: sqrt:4"<<endl;	break;

	case '3': cout<<"To take the N root of a number input nrt:a where n is the root and a is the number"
			" you are taking the root of."<<endl<<"Example: 2rt:4 or 3rt:9"<<endl;	break;

	case '4': cout<<"To find the logarithm of a number input log_b:n where b is the base and n is the number"
			" you are taking the logarithm of."<<endl<<"Example: log_2:4"<<endl;	break;

	case '5': cout<<"Here are some example inputs for this calculator:"<<endl<<"(1 + 2) / 3"<<endl<<"sqrt:4 + log_2:4"
			<<endl<<"2 ^ (10 / 2) * 4rt:16"<<endl;	break;

	case '0': cout<<"Have fun!"<<endl; return;

	default : cout<<"That is not a valid selection!"<<endl; break;
	}
	}

}

void mode(bool &debug)
{
	char selection;
	while(true)
	{
		cout<<"Available modes:"
			<<endl<<"1. Debug"
			<<endl<<"0. Quit"<<endl;
		cout<<endl<<"Input your selection: ";
		cin>>selection;
		cin.ignore();

		switch(selection)
		{
		case '1': if(debug == true)
				  {
					  debug = false;
					  cout<<endl<<"Debug mode has been turned off."<<endl;;
				  }
				  else
				  {
					  debug = true;
					  cout<<endl<<"Debug mode has been turned on."<<endl;;
				  }
					break;

		case '0': cout<<endl<<"Have fun!"<<endl;
				cout<<debug; return;

		default : cout<<endl<<"That is not a valid selection!"<<endl; break;
		}

	}
}

int main()
{
	//vector<Number> memory;


	//for testing
	/*string in = "1 +1";
	vector<char> test;

	try{
		test = shunt(in, true);
		cout<<endl<<endl<<"Input:  "<<in<<endl;
		cout<<"Final:  ";
		printVectorChar(test);}
	catch(exception& e){
		cout<<endl<<"ERROR: "<<e.what();}

	cout << endl;
	//Number* num = evalShunt(test);
	//num->print();

	/*Basic* a = new Basic(7);
	Basic* b = new Basic(12);
	Number* num = a->add(b);
	num->print();*/


	//Menu
	bool debug  = false;


	cout<<"If this is your first time using this calculator please check out \"Help\""<<endl;
	while(true)
	{
		string in;

		vector<char> test;
		char selection;
		Number* num;

		cout<<endl<<"What do you want to do?";
		cout<<endl<<"1. Input your expression"<<
		endl<<"2. Past results and set ANS"<<
		endl<<"3. Help"<<
		endl<<"4. Change modes"<<
		endl<<"0. Quit"<<
		endl<<endl<<"Input your selection: ";

		cin >> selection;
		cin.ignore();

		switch(selection)
		{
		case '1': cout<<"Input your expression: ";
						getline(cin, in);
						try{
								test = shunt(in, true);
								cout<<endl<<endl<<"Input:  "<<in<<endl;
								cout<<"Final:  ";
								printVectorChar(test);
								cout<<endl;
								num = evalShunt(test, debug);
								cout<<"Result: ";
								num->print();}
						catch(exception& e){
								cout<<endl<<"ERROR: "<<e.what();}
						break;

		case '2': cout<<"Under construction!"<<endl; break;//memory()

		case '3': help(); break;

		case '4': mode(debug); break;

		case '0': cout<<endl<<"Good bye!"; return 0;

		default: cout<<"You did not input a valid selection!"<<endl; break;
		}

	}

	return 0;

}
