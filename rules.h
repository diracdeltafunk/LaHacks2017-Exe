#ifndef rules_h
#define rules_h

#include "expression.h"
#include <vector>

using namespace std;

vector<Expression> CancelAdditive(const Expression& formula) {
    vector<Expression> list;
    if (formula.head->Type() == NodeType::Addition) {
        auto nodeAddends = dynamic_cast<AdditionNode*>(formula.head)->addends;
        for (const auto& term1 : nodeAddends) {
            for (const auto& term2 : nodeAddends) {
                if(term1->Type() == NodeType::Negation && *(dynamic_cast<NegationNode*>(term1)->getArg()) == *term2) {
                    nodeAddends.erase(term1);
                    nodeAddends.erase(term2);
                    list.push_back(Expression(new AdditionNode(nodeAddends)));
                    nodeAddends = dynamic_cast<AdditionNode*>(formula.head)->addends;
                }
            }
            for (const auto& expr : CancelAdditive(Expression(term1))){
                nodeAddends.erase(term1);
                nodeAddends.emplace(expr.head);
                list.push_back(Expression(new AdditionNode(nodeAddends)));
                nodeAddends = dynamic_cast<AdditionNode*>(formula.head)->addends;
            }
        }
        return list;
    }
    if(formula.head->arity() == 0) {
        return list;
    }
    if(formula.head->Type() == NodeType::Multiplication) {
        auto nodeFactors = dynamic_cast<ProductNode*>(formula.head)->factors;
        for (const auto& term1 : nodeFactors) {
            for (const auto& expr : CancelAdditive(Expression(term1))) {
                nodeFactors.erase(term1);
                nodeFactors.emplace(expr.head);
                list.push_back(Expression(new ProductNode(nodeFactors)));
                nodeFactors = dynamic_cast<ProductNode*>(formula.head)->factors;
            }
        }
        return list;
    }
    if(formula.head->Type() == NodeType::Exponentiation) {
        Node* Base = dynamic_cast<ExpNode*>(formula.head)->base;
        Node* Exponent = dynamic_cast<ExpNode*>(formula.head)->exponent;
        for(const auto & expr : CancelAdditive(Expression(Base))){
            list.push_back(Expression(new ExpNode(expr.head, Exponent)));
        }
        for(const auto & expr : CancelAdditive(Expression(Exponent))){
            list.push_back(Expression(new ExpNode(Base, expr.head)));
        }
        return list;
    }
    if (formula.head->arity() == 1) {
        Node* argument = dynamic_cast<Arity1Node*>(formula.head)->getArg();
        vector<Expression> nodelist = CancelAdditive(Expression(argument));
        for(const auto & expr : CancelAdditive(Expression(argument))) {
            list.push_back(Expression(formula.head->clone()->setArg(expr)));
        }
        return list;
    }
    return list;
}











vector<vector<pair <int, Expression>>> PatternList(const Expression& formula, const Expression& pattern){
    vector< vector<pair <int, Expression>> > list;
    
    if(formula.head->Type() != pattern.head->Type
       || pattern.head->arity() != formula.head->arity()){
        if(pattern.head->Type() == NodeType::PatternMatch){
            vector<pair <int, Expression>> singleton;
            singleton.push_back(make_pair(dynamic_cast<PatternMatchNode*>(pattern.head)->getIndex(),Expression(formula.head)));
            list.push_back(singleton);
        }else{
            return list;
        }
    }
    
    if(formula.head->Type() == NodeType::Addition) {
        auto FormulaList = dynamic_cast<AdditionNode*>(formula.head)->addends;
        auto PatternFirst = *((dynamic_cast<AdditionNode*>(pattern.head)->addends).begin());
        for(const auto& elmt: FormulaList){
            if(elmt->arity() == PatternFirst->arity()
               && elmt->Type() == PatternFirst->Type()){
                
                Expression formulaClone = formula;
                Expression patternClone = pattern;
                
                (dynamic_cast<AdditionNode*>(formulaClone.head)->addends).erase(elmt);
                (dynamic_cast<AdditionNode*>(patternClone.head)->addends).erase(PatternFirst);
                
                vector<vector<pair <int, Expression>>> V = PatternList(Expression(elmt), Expression(PatternFirst));
                vector<vector<pair <int, Expression>>> U = PatternList(formulaClone,patternClone);
                
                for(const auto& v: V){
                    for(const auto& u: U){
                        vector <int> was(100, 0);
                        vector<pair <int, Expression>> add;
                        bool flag = true;
                        for(const auto& x : v)
                            for(const auto& y : u)
                                if(x.first == y.first)
                                {
                                    if(x.second != y.second)
                                        flag = false;
                                    else if(!was[x.first])
                                    {
                                        was[x.first] = 1;
                                        add.push_back(x);
                                    }
                                }
                        if(flag)
                            list.push_back(add);
                        
                    }
                }
            }
        }
    }
    
    if(formula.head->Type() == NodeType::Multiplication) {
        auto FormulaList = dynamic_cast<ProductNode*>(formula.head)->factors;
        auto PatternFirst = *((dynamic_cast<ProductNode*>(pattern.head)->factors).begin());
        for(const auto& elmt: FormulaList){
            if(elmt->arity() == PatternFirst->arity()
               && elmt->Type() == PatternFirst->Type()){
                
                Expression formulaClone = formula;
                Expression patternClone = pattern;
                
                (dynamic_cast<ProductNode*>(formulaClone.head)->factors).erase(elmt);
                (dynamic_cast<ProductNode*>(patternClone.head)->factors).erase(PatternFirst);
                
                vector<vector<pair <int, Expression>>> V = PatternList(Expression(elmt), Expression(PatternFirst));
                vector<vector<pair <int, Expression>>> U = PatternList(formulaClone,patternClone);
                
                for(const auto& v: V){
                    for(const auto& u: U){
                        vector <int> was(100, 0);
                        vector<pair <int, Expression>> add;
                        bool flag = true;
                        for(const auto& x : v)
                            for(const auto& y : u)
                                if(x.first == y.first)
                                {
                                    if(x.second != y.second)
                                        flag = false;
                                    else if(!was[x.first])
                                    {
                                        was[x.first] = 1;
                                        add.push_back(x);
                                    }
                                }
                        if(flag)
                            list.push_back(add);
                        
                    }
                }
            }
        }
    }
    
    if(formula.head->Type() == NodeType::Exponentiation){
        
        vector<vector<pair <int, Expression>>> V = PatternList(Expression(dynamic_cast<ExpNode*>(formula.head)->base), Expression(dynamic_cast<ExpNode*>(pattern.head)->base));
        vector<vector<pair <int, Expression>>> U = PatternList(Expression(dynamic_cast<ExpNode*>(formula.head)->exponent), Expression(dynamic_cast<ExpNode*>(pattern.head)->exponent));
        
        for(const auto& v: V){
            for(const auto& u: U){
                vector <int> was(100, 0);
                vector<pair <int, Expression>> add;
                bool flag = true;
                for(const auto& x : v)
                    for(const auto& y : u)
                        if(x.first == y.first)
                        {
                            if(x.second != y.second)
                                flag = false;
                            else if(!was[x.first])
                            {
                                was[x.first] = 1;
                                add.push_back(x);
                            }
                        }
                if(flag)
                    list.push_back(add);
                
            }
        }
        
    }
    
    if(formula.head->isStrictArity1()){
        list = PatternList(Expression(dynamic_cast<Arity1Node*>(formula.head)->getArg()), Expression(dynamic_cast<Arity1Node*>(pattern.head)->getArg()));
    }
    
    if(formula.head->isStrictArity0()){
        if(*(formula.head) == *(pattern.head)){
            vector<pair <int, Expression>> xxx;
            list.push_back(xxx);
        }
    }
    
    return list;
}



class Rule{
public:
    Rule(const Expression& s,const Expression& f){
        start = Expression(s);
        finish = Expression(f);
    }
    Rule(Node* s,Node* f){
        start = Expression(s);
        finish = Expression(f);
    }
    Rule(const Rule& other){
        start = other.start;
        finish = other.finish;
    }
    
    vector<Expression> Apply(const Expression& formula){
        
    }
    
    
private:
    Expression start;
    Expression finish;
};














#endif
