#include "Log.h"

Log::Log(Number* co,Number* bas, Number* argu){
base = bas;
argument = argu;
coef = co;
type = "log";
}
Log::~Log()
{
	delete base;
	delete argument;
	delete coef;
}

Number* Log::add(Number* a){
if (a->getType() == "log"&&a->getBase() == base&&a->getNum() == argument){
Number* x = coef->add(a->getCoef());
Number* y = new Log(x, base, argument);
return y;
}
else{
vector<Number*> k;
k.push_back(this);
k.push_back(a);
Number* j = new Expression(k);
return j;
}

}

Number* Log::subtract(Number* a){
if (a->getType() == "log"&&a->getBase() == base&&a->getNum() == argument){
Number* x = coef->subtract(a->getCoef());
Number* y = new Log(x, base, argument);
return y;
}
else{
Number* i = new Basic(-1);
vector<Number*> k;
k.push_back(this);
k.push_back(a->multiply(i));
Number* j = new Expression(k);
return j;
}

}
Number* Log::multiply(Number* a){
return this;
}

Number* Log::divide(Number* a){
return this;
}

Number* Log::expo(Number* a){
return this;
}

int Log::getValue(){
return coef->getValue();
}

char Log::getCharValue(){
return '$';
}

Number* Log::simplifyHelper(){

return this;
}

string Log::getType(){
return type;
}

void Log::print(){
if (coef->getValue() != 1){
coef->print();
}
cout << "log_";
base->print();
cout << ':';
argument->print();


}

Number* Log::getNum(){
return this;
}

Number* Log::getDen(){
return this;
}

void Log::setNum(Number* a){

}

void Log::setDen(Number* a){

}

Number* Log::simplify(Number* a, int){
return this;
}

Number* Log::getCoef(){
return this;
}

Number* Log::getExp(){
return this;
}

Number* Log::getBase(){
return this;
}

vector<Number*> Log::getVect(){
Number* y = new Basic(1);
vector<Number*> x;
x.push_back(y);
return x;

}
void Log::setValue(int a)
{

}
Number* Log::log(Number*)
{
	return this;
}
void Log::simplify()
{

}


