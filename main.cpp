#include <iostream>
#include <set>
#include "expression.h"

using namespace std;

Expression id_f(Expression e) {
	if (e.head->Type() == NodeType::Negation) {
		return id_f(Expression(dynamic_cast<NegationNode*>(e.head)->getArg()));
	}
	return e;
}

int main()
{
	NegationNode* a = new NegationNode(new RationalNode(Rational(1, 2)));
	Expression y(a);
	cout << id_f(y) << endl;
    return 0;
}
