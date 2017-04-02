//
//  main.cpp
//  hacks_test
//
//  Created by kostya on 4/1/17.
//  Copyright © 2017 kostya. All rights reserved.
//

#include <iostream>
#include <bitset>
#include <vector>
#include <string>
#include "rules.h"
#include "expression.h"
#include "rand_func.h"
#include "simplify.h"

using namespace std;

vector<NodeType> allTypes = {
	NodeType::ConstantQ,      //0
    NodeType::ConstantPi,     //0
    NodeType::ConstantE,      //0
    NodeType::Identity,       //0
    NodeType::Addition,       //n
    NodeType::Multiplication, //n
    NodeType::Negation,       //1
    NodeType::Inversion,      //1
    NodeType::Exponentiation, //2
    NodeType::Logarithm,      //1
    NodeType::Sine,           //1
    NodeType::Cosine,         //1
    NodeType::ArcSin,         //1
    NodeType::ArcTan,         //1
};

vector<NodeType> types(string f) {
	vector<NodeType> result;
	for (int i = 0; i < f.size() && i < 14; ++i) {
		if (f[i] == '1') {
			result.push_back(allTypes[i]);
		}
	}
	return result;
}

int main(int argc, char** argv) {
	int height;
	vector<NodeType> flags;
	if (argc < 2)
		height = 2;
	else
		height = stoi(argv[1]);
	if (argc < 3)
		flags = types(string("11111111111111"));
	else
		flags = types(string(argv[2]));

	Expression e(rnd_func(flags, 0, height));
	Expression de = diff(e);
	cout << e << endl << de << endl;
    return 0;
}
