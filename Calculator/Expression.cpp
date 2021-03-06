#include "Expression.h"

Expression::Expression(vector<Number*> z) {
	expr = z;
	type = "expression";
}
Expression::~Expression() {
	delete this;
}

Number* Expression::add(Number* a) {
	if (a->getType() == "expression") {
		unsigned int t = 0;
		vector<Number*> boom;
		while (t < a->getVect().size()) {
			expr.push_back(a->getVect()[t]);
			t++;
		}
		boom = expr;
		Number* b = new Expression(boom);
		return b;

	} else {
		expr.push_back(a);
		vector<Number*> boom;
		boom = expr;
		Number* b = new Expression(boom);
		return b;
	}

}

Number* Expression::subtract(Number* a) {
	if (a->getType() == "expression") {
		unsigned int t = 0;
		Number* b = new Basic(-1);
		vector<Number*> g;
		while (t < a->getVect().size()) {
			Number* s = b->multiply(a->getVect()[t]);
			g.push_back(s);
			t++;
		}
		unsigned int u = 0;
		while (u < g.size()) {
			expr.push_back(g[u]);
			u++;
		}
		vector<Number*> v = expr;
		Number* j = new Expression(v);
		return j;
	}

	else {
		Number* b = new Basic(-1);
		vector<Number*> k = expr;
		k.push_back(a->multiply(b));
		Number* n = new Expression(k);
		return n;
	}

}

Number* Expression::multiply(Number* a) {
	return this;
}

Number* Expression::divide(Number* a) {
	return this;
}

Number* Expression::expo(Number* a) {
	return this;
}

int Expression::getValue() {
	return 479;
}

char Expression::getCharValue() {

	return '$';
}
//doesnt work 100% efficiently
Number* Expression::simplifyHelper() {
	if (expr.size() == 1) {
		return this;
	}
	vector<Number*> m;

	unsigned int t = 0;
	unsigned int k = 0;
	while (t < expr.size()) {
		k++;
		if (k != expr.size()) {
			//if (expr[t]->getType() == expr[k]->getType()){

			Number* b;
			b = expr[t]->add(expr[k]);

			if (b->getType() == "expression") {

				m.push_back(expr[t]);
				m.push_back(expr[k]);
				t += 2;
				if (k == expr.size() - 1 || k == expr.size()) {
					break;
				}
				k++;

			}
			if (b->getType() != "expression") {
				Number* z = b;

				m.push_back(z);
				//m[0]->print();

				t += 2;
				if (k == expr.size() - 1 || k == expr.size()) {
					break;
				}
				k++;

			}

//}

		} else {
			m.push_back(expr[k - 1]);
			break;
		}

	}
	Number* o = new Expression(m);
	o->print();
	cout << endl;
	if (m.size() == expr.size()) {
		return o;
	}
	return o->simplifyHelper();
}

string Expression::getType() {
	return type;
}

void Expression::print() {
	bool printn = false;
	Number* neg = new Basic(-1);
	unsigned int t = 0;
	while (t < expr.size()) {
		if (expr[t]->getValue() < 0||expr[t]->getCoef()->getValue() < 0) {
			printn = true;
			Number* n = expr[t]->multiply(neg);
			cout << "- ";
			n->print();
		} else if (expr[t]->getValue() > 0 && t != 0) {
			cout << "+ ";
		}
		if(!printn)
			expr[t]->print();
		cout << " ";

		t++;
	}

}

Number* Expression::getNum() {
	return this;

}

Number* Expression::getDen() {
	return this;
}

void Expression::setNum(Number* a) {

}

void Expression::setDen(Number* a) {

}

Number* Expression::simplify(Number* a, int b) {
	return this;
}

Number* Expression::getCoef() {
	return this;
}

Number* Expression::getExp() {
	return this;
}

Number* Expression::getBase() {
	return this;
}

vector<Number*> Expression::getVect() {
	return expr;
}
void Expression::setValue(int a) {

}
Number* Expression::log(Number* num) {
	return this;
}
void Expression::simplify() {

}

