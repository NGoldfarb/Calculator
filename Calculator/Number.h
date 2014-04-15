
 #ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include <iostream>
#include <vector>


using namespace std;

class Number{
    public:
        string type;
        virtual Number* add(Number*) = 0;
        virtual Number* subtract(Number*) = 0;
        virtual Number* multiply(Number*) = 0;
        virtual Number* divide(Number*) = 0;
        virtual int getValue() = 0;
        virtual void setValue(int)=0;
        virtual char getCharValue() = 0;
        //virtual Number* simplifyHelper() = 0;
        virtual void simplify()=0;
        virtual Number* expo(Number*) = 0;
        virtual Number* log(Number*) = 0;
        virtual string getType() = 0;
        virtual void print() = 0;
        virtual Number* getNum()=0;
        virtual Number* getDen()=0;
        virtual void setNum(Number*) = 0;
        virtual void setDen(Number*) = 0;
        //virtual Number* simplify(Number*,int) = 0;
        //for irrational class
        virtual Number* getCoef() = 0;
        virtual Number* getExp() = 0;
        //for exponent class
        virtual Number* getBase() = 0;

        virtual vector<Number*> getVect() = 0;
        virtual Number* simplifyHelper() = 0;

        virtual ~Number()  //had to add a virtual destructor
        {
        }

};

#endif /* NUMBER_H */
