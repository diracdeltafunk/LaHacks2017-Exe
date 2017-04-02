//
//  rand_func.h
//  hacks_test
//
//  Created by kostya on 4/2/17.
//  Copyright © 2017 kostya. All rights reserved.
//

#ifndef rand_func_h
#define rand_func_h

using namespace std;

Node* rnd_func(const vector<NodeType> &v, int depth, int max_depth)
{
	if(depth > max_depth)
	{
		if(rand() % 2)
		{
			int a = rand() % 20 + 1, b = rand() % 20 + 2;
			if(rand() % 2)
				return new RationalNode(Rational(a, b));
			else
				return new RationalNode(Rational(-a, b));
		}
		else
			return new IdentityNode;
	}
	else
	{
		int n = int(v.size()), num = rand() % n;
		if(v[num] == NodeType::ConstantQ || v[num] == NodeType::Identity)
			return rnd_func(v, depth, max_depth);
		if(v[num] == NodeType::Addition)
		{
			set <Node*> s;
			s.insert(rnd_func(v, depth + 1, max_depth));
			s.insert(rnd_func(v, depth + 1, max_depth));
			s.insert(rnd_func(v, depth + 1, max_depth));
			return new AdditionNode(s);
		}
		if(v[num] == NodeType::Multiplication)
		{
			set <Node*> s;
			s.insert(rnd_func(v, depth + 1, max_depth));
			s.insert(rnd_func(v, depth + 1, max_depth));
			s.insert(rnd_func(v, depth + 1, max_depth));
			return new ProductNode(s);
		}
		if(v[num] == NodeType::Negation)
		{
			return new NegationNode(rnd_func(v, depth + 1, max_depth));
		}
		if(v[num] == NodeType::Inversion)
		{
			return new InversionNode(rnd_func(v, depth + 1, max_depth));
		}
		if(v[num] == NodeType::Exponentiation)
		{
			return new ExpNode(rnd_func(v, depth + 1, max_depth), rnd_func(v, depth + 1, max_depth));
		}
		if(v[num] == NodeType::Logarithm)
		{
			return new LogNode(rnd_func(v, depth + 1, max_depth));
		}
		if(v[num] == NodeType::Sine)
		{
			return new SinNode(rnd_func(v, depth + 1, max_depth));
		}
		if(v[num] == NodeType::Cosine)
		{
			return new CosNode(rnd_func(v, depth + 1, max_depth));
		}
		if(v[num] == NodeType::ArcSin)
		{
			return new ArcSinNode(rnd_func(v, depth + 1, max_depth));
		}
		if(v[num] == NodeType::ArcTan)
		{
			return new ArcTanNode(rnd_func(v, depth + 1, max_depth));
		}
	}
	return nullptr;
}
#endif
