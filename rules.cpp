#include "rules.h"

using namespace std;

vector<vector<pair<int, Expression>>> PatternList(const Expression& formula, const Expression& pattern) {
    vector< vector<pair <int, Expression>> > list;

    if (formula.head->Type() != pattern.head->Type()
       || pattern.head->arity() != formula.head->arity()){
        if(pattern.head->Type() == NodeType::PatternMatch){
            vector<pair <int, Expression>> singleton;
            singleton.push_back(make_pair(dynamic_cast<PatternMatchNode*>(pattern.head)->getIndex(),Expression(formula.head)));
            list.push_back(singleton);
        }else{
            return list;
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

    else if (formula.head->Type() == NodeType::Multiplication) {
        auto FormulaList = dynamic_cast<ProductNode*>(formula.head)->factors;
        auto PatternFirst = *((dynamic_cast<ProductNode*>(pattern.head)->factors).begin());
        for(const auto& elmt: FormulaList){
            ((elmt->arity() == PatternFirst->arity()
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

    else if (formula.head->isStrictArity0()){
        if(*(formula.head) == *(pattern.head)){
            vector<pair<int, Expression>> xxx;
            list.push_back(xxx);
        }
    }

    return list;
}

vector<Expression> Rule::Apply(const Expression& formula) {

}
