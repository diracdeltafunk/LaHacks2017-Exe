#ifndef rules_h
#define rules_h

#include "expression.h"
#include <vector>

using namespace std;

vector<Expression> CancelAdditive(Expression formula){
    vector<Expression> list;
    if (formula.head->Type() == NodeType::Addition) {
        unordered_set<Node*> nodeAddends = dynamic_cast<AdditionNode*>(formula.head)->addends;
        for (const auto& term1 : nodeAddends) {
            for (const auto& term2 : nodeAddends) {
                if(term1->Type() == NodeType::Negation && *(term1->arg) == *term2) {
                    nodeAddends.erase(term1);
                    nodeAddends.erase(term2);
                    list.push_back(Expression(new AdditionNode(nodeAddends)));
                    nodeAddends = dynamic_cast<AdditionNode*>(formula.head)->addends;
                }
            }
            
            vector<Expression> nodelist = CancelAdditive(Expression(term1));
            for(auto & expr : nodelist){
                nodeAddends.erase(term1);
                nodeAddends.emplace(expr.head);
                list.push_back(Expression(new AdditionNode(nodeAddends)));
                nodeAddends = dynamic_cast<AdditionNode*>(formula.head)->addends;
            }
            
        }
        
    }else if(formula.head->Type() == NodeType::ConstantQ
             || formula.head->Type() == NodeType::ConstantPi
             || formula.head->Type() == NodeType::ConstantE
             || formula.head->Type() == NodeType::Identity){
        
        return list;
        
    }else if(formula.head->Type() == NodeType::Multiplication){
        
        for (const auto& term1 : nodeAddends) {
            vector<Expression> nodelist = CancelAdditive(Expression(term1));
            for(auto & expr : nodelist){
                nodeAddends.erase(term1);
                nodeAddends.emplace(expr.head);
                list.push_back(Expression(new AdditionNode(nodeAddends)));
                nodeAddends = dynamic_cast<AdditionNode*>(formula.head)->addends;
            }
            
        }
        
    }else if(formula.head->Type() == NodeType::Exponentiation){
        
        Node* Base = dynamic_cast<ExpNode*>(formula.head)->base;
        Node* Exponent = dynamic_cast<ExpNode*>(formula.head)->exponent;
        vector<Expression> nodelist1 = CancelAdditive(Expression(Base));
        for(auto & expr : nodelist1){
            list.push_back(Expression(new ExpNode(expr,Exponent)));
        }
        vector<Expression> nodelist2 = CancelAdditive(Expression(Exponent));
        for(auto & expr : nodelist2){
            list.push_back(Expression(new ExpNode(Base,expr)));
        }
        
    }else{
        
        Node* argument = dynamic_cast<Arity1Node*>(formula.head)->getArg();
        vector<Expression> nodelist = CancelAdditive(Expression(argument));
        for(auto & expr : nodelist){
            list.push_back(Expression(new Arity1Node(argument)));
        }
    }
    
}