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
#include "rand_func.h"

using namespace std;

vector<NodeType> types(bitset<14> flags) {
	vector<NodeType> result;
	for (int i = 0; i < 14; ++i)
		if (flags.test(i))
			result.push_back(static_cast<NodeType>(i));
	return result;
}

int main(int argc, char** argv) {
	int height;
	bitset<14> flags;
	if (argc < 2)
		height = 2;
	else
		height = stoi(argv[1]);
	if (argc < 3)
		flags = bitset<14>(string("11111111111111"));
	else
		flags = bitset<14>(string(argv[2]));
	cout << rnd_func(types(flags), 0, height)->getString() << endl;
    return 0;
}
