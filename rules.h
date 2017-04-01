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

#endif
