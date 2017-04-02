#include "rules.h"

using namespace std;

vector<vector<pair<int, Expression>>> PatternList(const Expression& formula, const Expression& pattern) {
    vector<vector<pair<int, Expression>>> list;

    if (formula.head->Type() != pattern.head->Type()
       || pattern.head->arity() != formula.head->arity()){
        if(pattern.head->Type() == NodeType::PatternMatch){
            vector<pair <int, Expression>> singleton;
            singleton.push_back(make_pair(dynamic_cast<PatternMatchNode*>(pattern.head)->getIndex(),formula));
            list.push_back(singleton);
        }else{
            return list;
        }
    }
    
    else if (formula.head->arity() == 0){
        if(*(formula.head) == *(pattern.head)){
            vector<pair<int, Expression>> xxx;
            list.push_back(xxx);
        }
    }

    else if (formula.head->Type() == NodeType::Addition) {
        auto FormulaList = dynamic_cast<AdditionNode*>(formula.head)->addends;
        auto PatternFirst = *((dynamic_cast<AdditionNode*>(pattern.head)->addends).begin());
        for(const auto& elmt: FormulaList){
            if((elmt->arity() == PatternFirst->arity()
               && elmt->Type() == PatternFirst->Type())
               || PatternFirst->Type()== NodeType::PatternMatch){

                Expression formulaClone = formula;
                Expression patternClone = pattern;

                (dynamic_cast<AdditionNode*>(formulaClone.head)->addends).erase(elmt);
                (dynamic_cast<AdditionNode*>(patternClone.head)->addends).erase(PatternFirst);

                vector<vector<pair <int, Expression>>> V = PatternList(Expression(elmt->clone()), Expression(PatternFirst->clone()));
                vector<vector<pair <int, Expression>>> U = PatternList(formulaClone, patternClone);

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

    else if (formula.head->Type() == NodeType::Multiplication) {
        auto FormulaList = dynamic_cast<ProductNode*>(formula.head)->factors;
        auto PatternFirst = *((dynamic_cast<ProductNode*>(pattern.head)->factors).begin());
        for(const auto& elmt : FormulaList){
            if((elmt->arity() == PatternFirst->arity()
              && elmt->Type() == PatternFirst->Type())
             || PatternFirst->Type()== NodeType::PatternMatch){

                Expression formulaClone = formula;
                Expression patternClone = pattern;

                (dynamic_cast<ProductNode*>(formulaClone.head)->factors).erase(elmt);
                (dynamic_cast<ProductNode*>(patternClone.head)->factors).erase(PatternFirst);

                vector<vector<pair <int, Expression>>> V = PatternList(Expression(elmt->clone()), Expression(PatternFirst->clone()));
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

    else if (formula.head->Type() == NodeType::Exponentiation){

        vector<vector<pair <int, Expression>>> V = PatternList(Expression(dynamic_cast<ExpNode*>(formula.head)->base->clone()), Expression(dynamic_cast<ExpNode*>(pattern.head)->base->clone()));
        vector<vector<pair <int, Expression>>> U = PatternList(Expression(dynamic_cast<ExpNode*>(formula.head)->exponent->clone()), Expression(dynamic_cast<ExpNode*>(pattern.head)->exponent->clone()));

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

    else if (formula.head->isStrictArity1()){
        list = PatternList(Expression(dynamic_cast<Arity1Node*>(formula.head)->getArg()->clone()), Expression(dynamic_cast<Arity1Node*>(pattern.head)->getArg()->clone()));
    }

    return list;
}

Expression replace(vector<pair<int, Expression>> replacements, Expression Base){
    if(Base.head->Type() == NodeType::PatternMatch){
        for(const auto& v:replacements){
            if(v.first == dynamic_cast<PatternMatchNode*>(Base.head)->getIndex()){
                return v.second;
            }
        }
    }
    else if(Base.head->Type() == NodeType::Addition){
        Expression baseClone = Base;
        for(auto& child : dynamic_cast<AdditionNode*>(baseClone.head)->addends){
            child = replace(replacements, Expression(child->clone())).head;
        }
        return baseClone;
    }
    else if(Base.head->Type() == NodeType::Multiplication){
        Expression baseClone = Base;
        for(auto& child : dynamic_cast<ProductNode*>(baseClone.head)->factors){
            child = replace(replacements, Expression(child->clone())).head;
        }
        return baseClone;
    }
    else if(Base.head->Type() == NodeType::Exponentiation){
        Expression baseClone = Base;
        Node* child1 = dynamic_cast<ProductNode*>(baseClone.head)->base;
        Node* child2 = dynamic_cast<ProductNode*>(baseClone.head)->exponent;
        *child1 = *(replace(replacements, Expression(child1->clone())).head);
        *child2 = *(replace(replacements, Expression(child2->clone())).head);
        return baseClone;
    }
    else if(Base.head->isStrictArity1()){
        Expression baseClone = Base;
        Node* child = dynamic_cast<Arity1Node>(baseClone.head)->getArg();
        baseClone.setArg(replace(replacements, Expression(child->clone())).head);
        return baseClone;
    }
    return base;
}

vector<Expression> Rule::Apply(const Expression& formula) {
    vector<Expression> list;
    
    for(const auto& replacements: PatternList(formula, start)){
        list.push_back(replace(replacements, formula))
    }
    
    if (formula.head->Type() == NodeType::Addition){
        auto nodeAddends = dynamic_cast<AdditionNode*>(formula.head)->addends;
        for (auto& term : nodeAddends) {
            for (const auto& expr : Apply(Expression(term->clone()))){
                term = expr.head;
                list.push_back(Expression(new AdditionNode(nodeAddends)));
                nodeAddends = dynamic_cast<AdditionNode*>(formula.head)->addends;
            }
        }
    }
    
    if (formula.head->Type() == NodeType::Multiplication){
        auto nodeFactors = dynamic_cast<ProductNode*>(formula.head)->factors;
        for (auto& term : nodeFactors) {
            for (const auto& expr : Apply(Expression(term->clone()))){
                term = expr.head;
                list.push_back(Expression(new productNode(nodeFactors)));
                nodeFactors = dynamic_cast<ProductNode*>(formula.head)->factors;
            }
        }
    }
    
    if (formula.head->Type() == NodeType::Exponentiation){
        Node* Base = dynamic_cast<ExpNode*>(formula.head)->base;
        Node* Exponent = dynamic_cast<ExpNode*>(formula.head)->exponent;
        for(const auto & expr : Apply(Expression(Base))){
            list.push_back(Expression(new ExpNode(expr.head, Exponent)));
        }
        for(const auto & expr : Apply(Expression(Exponent))){
            list.push_back(Expression(new ExpNode(Base, expr.head)));
        }
        return list;
    }
    
    if (formula.head->isStrictArity1()) {
        Node* argument = dynamic_cast<Arity1Node*>(formula.head)->getArg();
        for(const auto & expr : Apply(Expression(argument))) {
            list.push_back(Expression(dynamic_cast<Arity1Node*>(formula.head->clone())->setArg(expr.head)));
        }
        return list;
    }
        
    return list;
}





