#include "Basic.h"

Basic::Basic(int n){
    value = n;
    type = "basic";
}

Number* Basic::add(Number* n){
    Basic* x = new Basic(value + n->getValue());
        return x;
}

Number* Basic::subtract(Number* n){
    Basic* x = new Basic(value - n->getValue());
    return x;
}

Number* Basic::multiply(Number* n){
    Basic* x = new Basic(value*n->getValue());
    return x;
}

Number* Basic::divide(Number* n){
    if (value%n->getValue() == 0){
        Basic* x = new Basic(value / n->getValue());
            return x;
    }

    else{
        Basic* y = new Basic(n->getValue());
        Number* a = new Fraction(this, y);
        return a->simplifyHelper();
    }
}

Number* Basic::expo(Number* n){  //needs further implentation if the parameter number is not a basic or is negative etc
    int a = 1;
    int b = 1;
    while (a < n->getValue() + 1){
        b *= value;
        a++;
    }
    Basic* d = new Basic(b);
    return d;
}

Number* Basic::simplifyHelper(){
    return this;
}

int Basic::getValue(){
    return value;
}

void Basic::print(){

    if (value != 1){
        cout << value;
    }

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

Number* Basic::simplify(Number* a, int n){
    return this;
}

Number* Basic::getCoef(){
    return this;
}

Number* Basic::getExp(){
    return this;
}

Number* Basic::getBase(){
    return this;
}


