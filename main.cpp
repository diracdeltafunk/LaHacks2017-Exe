#include <iostream>
#include <set>
#include "rules.hpp"

using namespace std;

int main()
{
//	RationalNode l(Rational(1, 2)), r(Rational(1, 1));
	set<Node*> c;
	c.insert(new SinNode(new IdentityNode));
	c.insert(new NegationNode(new SinNode(new IdentityNode)));
	c.insert(new NegationNode(new SinNode(new IdentityNode)));
	Expression expr(new AdditionNode(c));
	set<Node*> cp;
	cp.insert(new PatternMatchNode(0));
	
	cp.insert(new NegationNode(new PatternMatchNode(0)));
	
	Expression exprp(new AdditionNode(cp));
	vector <vector <pair <int, Expression>>> v = PatternList(expr, exprp);
	cout << v.size() << "\n";
    return 0;
}
