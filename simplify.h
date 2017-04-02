#ifndef simplify_h
#define simplify_h
#include <set>
#include "rules.hpp"
#include "Rational.hpp"
#include "expression.hpp"

using namespace std;

int K = 4;

vector<Rule*> generateSimps() {
	vector<Rule*> SimpList;
	
	for(int k = 0; k < K; k++) {
		set<Node*> cp;
		cp.insert(new PatternMatchNode(0));
		cp.insert(new NegationNode(new PatternMatchNode(0)));
		for(int i = 0; i < k; i++){
			cp.insert(new PatternMatchNode(i+1));
		}
		Expression cancel(new AdditionNode(cp));
		
		set<Node*> cc;
		for(int i = 0; i < k; i++){
			cc.insert(new PatternMatchNode(i+1));
		}
		Expression empt(new AdditionNode(cc));
		
		Rule* R1 = new Rule(cancel, empt);
		
		SimpList.push_back(R1);
		
		
		set<Node*> cp2;
		cp2.insert(new PatternMatchNode(0));
		cp2.insert(new InversionNode(new PatternMatchNode(0)));
		for(int i = 0; i < k; i++){
			cp2.insert(new PatternMatchNode(i+1));
		}
		Expression cancel2(new ProductNode(cp2));
		
		set<Node*> cc2;
		for(int i = 0; i < k; i++){
			cc2.insert(new PatternMatchNode(i+1));
		}
		Expression empt2(new ProductNode(cc2));
		
		Rule* R2 = new Rule(cancel2, empt2);
		SimpList.push_back(R2);
		
		
		for(int l = 0; l < K; l++){
			
			set<Node*> adlst1;
			for(int i = 0; i < l; i++){
				adlst1.insert(new PatternMatchNode(i));
			}
			set<Node*> prlst1;
			prlst1.insert(new AdditionNode(adlst1));
			for(int j = 0; j < k; j++){
				prlst1.insert(new PatternMatchNode(j+l));
			}
			Expression dist1(new ProductNode(prlst1));
			
			set<Node*> adlst2;
			for(int i = 0; i < l; i++) {
				set<Node*> prlst2;
				prlst2.insert(new PatternMatchNode(i));
				for(int j = 0; j < k; j++){
					prlst2.insert(new PatternMatchNode(j+l));
				}
				adlst2.insert(new ProductNode(prlst2));
			}
			Expression dist2(new AdditionNode(adlst2));
			
			Rule* R3 = new Rule(dist1, dist2);
			SimpList.push_back(R3);
			
			Rule* R4 = new Rule(dist2, dist1);
			SimpList.push_back(R4);
		}
		
		
		set<Node*> sm1;
		for(int i = 0; i < k; i++){
			sm1.insert(new PatternMatchNode(i));
		}
		Expression an1(new NegationNode(new AdditionNode(sm1)));
		set<Node*> ms1;
		for(int i = 0; i < k; i++){
			ms1.insert(new NegationNode(new PatternMatchNode(i)));
		}
		Expression an2(new AdditionNode(ms1));
		Rule* R5 = new Rule(an1, an2);
		SimpList.push_back(R5);
		Rule* R6 = new Rule(an2, an1);
		SimpList.push_back(R6);
		
		
		set<Node*> sm2;
		for(int i = 0; i < k; i++){
			sm2.insert(new PatternMatchNode(i));
		}
		Expression pn1(new InversionNode(new ProductNode(sm2)));
		set<Node*> ms2;
		for(int i = 0; i < k; i++){
			ms2.insert(new InversionNode(new PatternMatchNode(i)));
		}
		Expression pn2(new ProductNode(ms2));
		Rule* R7 = new Rule(pn1, pn2);
		SimpList.push_back(R7);
		Rule* R8 = new Rule(pn2, pn1);
		SimpList.push_back(R8);
		
		
		set<Node*> nm;
		nm.insert(new NegationNode(new PatternMatchNode(0)));
		for(int i = 0; i < k; i++){
			nm.insert(new PatternMatchNode(i+1));
		}
		Expression negmult(new ProductNode(nm));
		set<Node*> mn;
		for(int i = 0; i < k+1; i++){
			mn.insert(new PatternMatchNode(i));
		}
		Expression multneg(new NegationNode(new ProductNode(mn)));
		Rule* R9 = new Rule(negmult,multneg);
		SimpList.push_back(R9);
		Rule* R10 = new Rule(multneg,negmult);
		SimpList.push_back(R10);
		
		
		set<Node*> ra;
		for(int i = 0; i < k; i++){
			ra.insert(new PatternMatchNode(0));
		}
		Expression repad(new AdditionNode(ra));
		set<Node*> ml;
		ml.insert(new RationalNode(Rational(k,1)));
		ml.insert(new PatternMatchNode(0));
		Expression natmult(new ProductNode(ml));
		if(k > 0){
			Rule* R11 = new Rule(repad,natmult);
			SimpList.push_back(R11);
		}
		Rule* R12 = new Rule(natmult,repad);
		SimpList.push_back(R12);
		
        set<Node*> ra2;
        for(int i = 0; i < k; i++){
            ra2.insert(new PatternMatchNode(0));
        }
		Expression reppr(new ProductNode(ra2));
		Expression natexp(new ExpNode(new PatternMatchNode(0), new RationalNode(Rational(k,1)) ));
		if(k > 0){
			Rule* R13 = new Rule(reppr,natexp);
			SimpList.push_back(R13);
		}
		Rule* R14 = new Rule(natexp,reppr);
		SimpList.push_back(R14);
		
		
		set<Node*> vars;
		for(int i = 0; i < k; i++){
			vars.insert(new PatternMatchNode(i));
		}
		set<Node*> zer;
		for(int i = 0; i < k; i++){
			zer.insert(new PatternMatchNode(i));
		}
		zer.insert(new RationalNode(Rational(0,1)));
		set<Node*> uni;
		for(int i = 0; i < k; i++){
			uni.insert(new PatternMatchNode(i));
		}
		uni.insert(new RationalNode(Rational(0,1)));
		Expression prdct(new ProductNode(vars));
		Expression sumex(new AdditionNode(vars));
		Expression prduni(new ProductNode(uni));
		Expression sumzer(new AdditionNode(zer));
		
		Rule* T5 = new Rule(prdct, prduni);
		SimpList.push_back(T5);
		Rule* T6 = new Rule(prduni, prdct);
		SimpList.push_back(T6);
		Rule* T7 = new Rule(sumex, sumzer);
		SimpList.push_back(T7);
		Rule* T8 = new Rule(sumzer, sumex);
		SimpList.push_back(T8);
		
		
	}
	
	set<Node*> empty;
	Expression emptsum(new AdditionNode(empty));
	Expression emptprd(new ProductNode(empty));
	Expression zerorat(new RationalNode(Rational(0,1)));
	Expression onerat(new RationalNode(Rational(1,1)));
	
	Rule* T1 = new Rule(emptsum, zerorat);
	SimpList.push_back(T1);
	Rule* T2 = new Rule(zerorat, emptsum);
	SimpList.push_back(T2);
	Rule* T3 = new Rule(emptprd, onerat);
	SimpList.push_back(T3);
	Rule* T4 = new Rule(onerat, emptprd);
	SimpList.push_back(T4);
	
	Expression neg2(new NegationNode(new NegationNode(new PatternMatchNode(0))));
	Expression inv2(new InversionNode(new InversionNode(new PatternMatchNode(0))));
	Expression lolnothing(new PatternMatchNode(0));
	
	Rule* D1 = new Rule(neg2,lolnothing);
	SimpList.push_back(D1);
	Rule* D2 = new Rule(inv2,lolnothing);
	SimpList.push_back(D2);
	Rule* D3 = new Rule(lolnothing,neg2);
	SimpList.push_back(D3);
	Rule* D4 = new Rule(lolnothing,inv2);
	SimpList.push_back(D4);
	
	Expression tomin(new ExpNode(new PatternMatchNode(0), new NegationNode(new PatternMatchNode(1))));
	Expression recto(new ExpNode(new InversionNode(new PatternMatchNode(0)), new PatternMatchNode(1)));
	Expression recpow(new InversionNode(new ExpNode(new PatternMatchNode(0), new PatternMatchNode(1))));
	
	Rule* E1 = new Rule(tomin, recto);
	SimpList.push_back(E1);
	Rule* E2 = new Rule(recto, tomin);
	SimpList.push_back(E2);
	Rule* E3 = new Rule(recto, recpow);
	SimpList.push_back(E3);
	Rule* E4 = new Rule(recpow, recto);
	SimpList.push_back(E4);
	
	set<Node*> xy;
	xy.insert(new PatternMatchNode(0));
	xy.insert(new PatternMatchNode(1));
	Expression xyz(new ExpNode(new ProductNode(xy), new PatternMatchNode(2)));
	set<Node*> xzyz;
	xzyz.insert(new ExpNode(new PatternMatchNode(0),new PatternMatchNode(2)));
	xzyz.insert(new ExpNode(new PatternMatchNode(1), new PatternMatchNode(2)));
	Expression xyz2(new ProductNode(xzyz));
	Rule* E5 = new Rule(xyz,xyz2);
	SimpList.push_back(E5);
	Rule* E6 = new Rule(xyz2,xyz);
	SimpList.push_back(E6);
	
	Expression zxy(new ExpNode(new PatternMatchNode(2), new ProductNode(xy)));
	Expression ztytx(new ExpNode(new ExpNode(new PatternMatchNode(2), new PatternMatchNode(1)),new PatternMatchNode(0) ));
	Rule* E7 = new Rule(zxy,ztytx);
	SimpList.push_back(E7);
	Rule* E8 = new Rule(ztytx,zxy);
	SimpList.push_back(E8);
	
	Expression zxpy(new ExpNode(new PatternMatchNode(2), new AdditionNode(xy)));
	set<Node*> zxzy;
	zxzy.insert(new ExpNode(new PatternMatchNode(2),new PatternMatchNode(0)));
	zxzy.insert(new ExpNode(new PatternMatchNode(2), new PatternMatchNode(1)));
	Expression zxy2(new ProductNode(zxzy));
	Rule* E9 = new Rule(zxpy,zxy2);
	SimpList.push_back(E9);
	Rule* E10 = new Rule(zxy2,zxpy);
	SimpList.push_back(E10);
	
	Expression lxy(new LogNode(new ProductNode(xy)));
	set<Node*> lxly;
	lxly.insert(new LogNode(new PatternMatchNode(0)));
	lxly.insert(new LogNode(new PatternMatchNode(1)));
	Expression lxy2(new AdditionNode(lxly));
	Rule* L1 = new Rule(lxy,lxy2);
	SimpList.push_back(L1);
	Rule* L2 = new Rule(lxy2,lxy);
	SimpList.push_back(L2);
	
	Expression lxty(new LogNode(new ExpNode(new PatternMatchNode(0),new PatternMatchNode(1))));
	set<Node*> ylx;
	ylx.insert(new PatternMatchNode(1));
	ylx.insert(new LogNode(new PatternMatchNode(0)));
	Expression lxty2(new ProductNode(ylx));
	Rule* L3 = new Rule(lxty,lxty2);
	SimpList.push_back(L3);
	Rule* L4 = new Rule(lxty2,lxty);
	SimpList.push_back(L4);
	
	Expression ytlx(new ExpNode(new PatternMatchNode(1), new LogNode(new PatternMatchNode(0))));
	Expression xtly(new ExpNode(new PatternMatchNode(0), new LogNode(new PatternMatchNode(1))));
	Rule* L5 = new Rule(ytlx,xtly);
	SimpList.push_back(L5);
	Rule* L6 = new Rule(ytlx,xtly);
	SimpList.push_back(L6);
	
	Expression lrec(new LogNode(new InversionNode(new PatternMatchNode(0))));
	Expression negl(new NegationNode(new LogNode(new PatternMatchNode(0))));
	Rule* L7 = new Rule(lrec,negl);
	SimpList.push_back(L7);
	Rule* L8 = new Rule(negl,lrec);
	SimpList.push_back(L8);
	
	set<Node*> sinsum;
	sinsum.insert(new ExpNode(new SinNode(new PatternMatchNode(0)),new RationalNode(Rational(2,1))));
	sinsum.insert(new ExpNode(new CosNode(new PatternMatchNode(0)),new RationalNode(Rational(2,1))));
	Expression s2c2(new AdditionNode(sinsum));
	Rule* S1 = new Rule(s2c2, onerat);
	SimpList.push_back(S1);
	
	
	return SimpList;
}

int measure(Node* formula){
	if(formula->Type() == NodeType::Addition ){
		int sum = 1;
		for(const auto& term : dynamic_cast<AdditionNode*>(formula)->addends ){
			sum += measure(term->clone());
		}
		return sum;
	}
	if(formula->Type() == NodeType::Multiplication ){
		int sum = 1;
		for(const auto& term : dynamic_cast<ProductNode*>(formula)->factors ){
			sum += measure(term->clone());
		}
		return sum;
	}
	if(formula->Type() == NodeType::Exponentiation){
		return 1 + measure(dynamic_cast<ExpNode*>(formula)->base->clone()) + measure(dynamic_cast<ExpNode*>(formula)->exponent->clone());
	}
	if(formula->isStrictArity1()){
		return 1 + measure(dynamic_cast<Arity1Node*>(formula)->getArg()->clone());
	}
	return 1;
}

Expression Simplify(vector<Rule*> ruleList, Expression formula){
	Expression best(formula);
	int record = 1000;
	for(const auto& rule : ruleList){
		for(const auto& term: rule->Apply(formula)){
			if (measure(term.head->clone())< record){
				best = term;
				record = measure(term.head->clone());
			}
		}
	}
	return best;
}

#endif
