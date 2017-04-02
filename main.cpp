//
//  main.cpp
//  hacks_test
//
//  Created by kostya on 4/1/17.
//  Copyright © 2017 kostya. All rights reserved.
//

#include <iostream>
#include <set>
#include "rules.hpp"

using namespace std;

int main()
{
//	RationalNode l(Rational(1, 2)), r(Rational(1, 1));
	set<Node*> c, c1;
	c.insert(new IdentityNode);
	c.insert(new NegationNode(new IdentityNode));
	c1.insert(new IdentityNode);
	c1.insert(new NegationNode(new IdentityNode));
	set <Node*> ccc;
	ccc.insert(new SinNode(new AdditionNode(c)));
	ccc.insert(new NegationNode(new SinNode(new AdditionNode(c1))));
	Expression expr(new AdditionNode(ccc));
//	Expression expr0(new AdditionNode(c));
	
	set<Node*> cc;
	Expression empt(new AdditionNode(cc));
	
	set<Node*> cp;
	cp.insert(new PatternMatchNode(0));
	cp.insert(new NegationNode(new PatternMatchNode(0)));
	Expression amina(new AdditionNode(cp));
	
	Rule R(amina, empt);
	
//	vector<pair<int, Expression>> replace_tester;
//	replace_tester.push_back(make_pair(0, Expression(new RationalNode(Rational(1,1)))));
	
//	cout << replace(replace_tester, amina) << endl;
	
	vector <Expression> v = R.Apply(expr);
	
//	vector <vector <pair <int, Expression>>> v = PatternList(expr, exprp);
	cout << v.size() << "\n";
//	for(int i = 0; i < v.size(); i++)
//		cout << v[i].size() << " ";
//	cout << "\n";
    return 0;
}
