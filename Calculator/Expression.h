
Drive
CREATE
My Drive
Shared with Me

Starred

Recent

Trash

More

Install Drive for your computer
1.32 GB (8%) of 15 GB used
Manage
Calcfiles
J
D
N
Z

Calcfiles
TITLE
OWNER
LAST MODIFIED
Plain Textnumberh.txtShared
Justin Lauk
2:54 pm‎Justin Lauk
Plain Textlogh.txtShared
Justin Lauk
2:53 pm‎Justin Lauk
Plain Textlogcpp.txtShared
Justin Lauk
2:53 pm‎Justin Lauk
Plain Textirrationalh.txtShared
Justin Lauk
2:53 pm‎Justin Lauk
Plain Textirrationalcpp.txtShared
Justin Lauk
2:53 pm‎Justin Lauk
Plain Textfractionh.txtShared
Justin Lauk
2:53 pm‎Justin Lauk
Plain Textfractioncpp.txtShared
Justin Lauk
2:53 pm‎Justin Lauk
Plain Textexpressionh.txtShared
Justin Lauk
2:53 pm‎Justin Lauk
Plain Textexpressioncpp.txtShared
Justin Lauk
2:53 pm‎Justin Lauk
Plain Textexponenth.txtShared
Justin Lauk
2:53 pm‎Justin Lauk
Plain Textexponentcpp.txtShared
Justin Lauk
2:53 pm‎Justin Lauk
Plain Textbasich.txtShared
Justin Lauk
2:53 pm‎Justin Lauk
Plain Textbasiccpp.txtShared
Justin Lauk
2:53 pm‎Justin Lauk
DETAILSACTIVITY
TODAY
J
2:54 PM
Justin Lauk
shared 14 items
Text
basiccpp.txt
Text
exponentcpp.txt
Text
basich.txt
Text
fractionh.txt
Text
irrationalcpp.txt
Text
fractioncpp.txt
Show all...
N
Can edit
You
Z
Can edit
Zach Higgins
D
Can edit
Daniel Edgington
J
2:54 PM
Justin Lauk
uploaded 13 items
Text
numberh.txt
Text
logh.txt
Text
logcpp.txt
Text
irrationalh.txt
Text
irrationalcpp.txt
Text
fractionh.txt
Show all...
J
2:53 PM
Justin Lauk
uploaded an item
Google Drive Folder
Calcfiles
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include <iostream>
#include "Number.h"
#include "Basic.h"

using namespace std;

class Expression : public Number{
public:
Expression(vector<Number*>);
~Expression();

vector<Number*> expr;

string type;
Number* add(Number*) ;
Number* subtract(Number*) ;
Number* multiply(Number*) ;
Number* divide(Number*) ;
int getValue() ;
char getCharValue() ;
Number* simplifyHelper() ;
Number* expo(Number*) ;
string getType() ;
void print() ;
Number* getNum() ;
Number* getDen() ;
void setNum(Number*) ;
void setDen(Number*) ;
Number* simplify(Number*, int) ;
//for irrational class
Number* getCoef() ;
Number* getExp() ;
//for exponent class
Number* getBase() ;
//for expression
vector<Number*> getVect();

};




#endif /* EXPRESSION_H */
