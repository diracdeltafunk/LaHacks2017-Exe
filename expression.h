//
//  expression.h
//  LaHacks2017
//
//  Created by Kyle Hess on 4/1/17.
//  Copyright © 2017 Kyle Hess. All rights reserved.
//

#ifndef expression_h
#define expression_h

#include <unordered_set>
#include "rational.h"

enum NodeType {     //Arity:
    ConstantQ,      //0
    ConstantPi,     //0
    ConstantE,      //0
    Identity,       //0
    Addition,       //n
    Multiplication, //n
    Negation,       //1
    Inversion,      //1
    Exponentiation, //2
    Logarithm,      //1
    Sine,           //1
    Cosine,         //1
    ArcSin,         //1
    ArcTan,         //1
    PatternMatch    //-1
};

class Node {
public:
    virtual ~Node();
    virtual Node* clone() const = 0;
    virtual NodeType Type() const = 0;
    virtual unsigned arity() const = 0;
    virtual bool isStrictArity1() const { return false; }
    virtual bool hasPattern() const = 0;
    virtual bool isEqual(Node const * const) const = 0;
    bool operator==(const Node& other) const {
        return other.isEqual(this);
    }
};

typedef std::unordered_set<Node*> collection_t;

bool same_collection(collection_t a, collection_t b) {
    for (const auto& x : a) {
        for (const auto& y : b) {
            if (x->isEqual(y)) {
                a.erase(x);
                b.erase(y);
                return same_collection(a,b);
            }
        }
        return false;
    }
    return b.empty();
}

class Arity0Node : public Node {
public:
    unsigned arity() const { return 0; }
    bool hasPattern() const { return false; }
};

class Arity1Node : public Node {
public:
    unsigned arity() const { return 1; }
    bool isStrictArity1() const { return true; }
    virtual Node* getArg() const = 0;
    virtual Node* setArg(Node* newArg) = 0;
    bool hasPattern() const { return getArg()->hasPattern(); }
    bool isEqual(Node const * const other) const {
        return (other->Type() == this->Type()) && (this->getArg()->isEqual(dynamic_cast<Arity1Node const * const>(other)->getArg()));
    }
};

class RationalNode : public Arity0Node {
public:
    RationalNode(Rational init_q) : q(init_q) {}

    RationalNode* clone() const {
        return new RationalNode(*this);
    }

    NodeType Type() const { return NodeType::ConstantQ; }

    Rational getNumber() const { return q; }

    bool isEqual(Node const * const other) const {
        return (other->Type() == NodeType::ConstantQ) && (dynamic_cast<RationalNode const * const>(other)->getNumber() == q);
    }

private:
    Rational q;
};

class PiNode : public Arity0Node {
public:
    NodeType Type() const { return NodeType::ConstantPi; }

    PiNode* clone() const {
        return new PiNode;
    }

    bool isEqual(Node const * const other) const {
        return other->Type() == NodeType::ConstantPi;
    }
};

class ENode : public Arity0Node {
public:
    NodeType Type() const { return NodeType::ConstantE; }

    ENode* clone() const {
        return new ENode;
    }

    bool isEqual(Node const * const other) const {
        return other->Type() == NodeType::ConstantPi;
    }
};

class IdentityNode : public Arity0Node {
public:
    NodeType Type() const { return NodeType::Identity; }

    IdentityNode* clone() const {
        return new IdentityNode;
    }

    bool isEqual(Node const * const other) const {
        return other->Type() == NodeType::Identity;
    }
};

class AdditionNode : public Node {
public:
    AdditionNode(collection_t init_addends) : addends(init_addends) {}

    ~AdditionNode() {
        for (auto x : addends)
            delete x;
    }

    AdditionNode* clone() const {
        collection_t newAddends;
        for (const auto& a : addends)
            newAddends.insert(a->clone());
        return new AdditionNode(newAddends);
    }

    NodeType Type() const { return NodeType::Addition; }

    unsigned arity() const { return addends.size(); }

    bool hasPattern() const {
        for (const auto& a : addends) {
            if (a->hasPattern())
                return false;
        }
        return true;
    }

    bool isEqual(Node const * const other) const {
        if ((other->Type() != NodeType::Addition) || (arity() != other->arity()))
            return false;
        return same_collection(addends, dynamic_cast<AdditionNode const * const>(other)->addends);
    }

    collection_t addends;
};

class ProductNode : public Node {
public:
    ProductNode(collection_t init_factors) : factors(init_factors) {}

    ~ProductNode() {
        for (auto x : factors)
            delete x;
    }

    ProductNode* clone() const {
        collection_t newFactors;
        for (auto f : factors)
            newFactors.insert(f->clone());
        return new ProductNode(newFactors);
    }

    NodeType Type() const { return NodeType::Multiplication; }

    unsigned arity() const { return factors.size(); }

    bool hasPattern() const {
        for (const auto& a : factors) {
            if (a->hasPattern())
                return false;
        }
        return true;
    }

    bool isEqual(Node const * const other) const {
        if ((other->Type() != NodeType::Multiplication) || (arity() != other->arity()))
            return false;
        return same_collection(factors, dynamic_cast<ProductNode const * const>(other)->factors);
    }

    collection_t factors;
};

class NegationNode : public Arity1Node {
public:
    NegationNode(Node* init_arg) : arg(init_arg) {}

    ~NegationNode() {
        delete arg;
    }

    NegationNode* clone() const {
        return new NegationNode(arg->clone());
    }

    NodeType Type() const { return NodeType::Negation; }

    Node* getArg() const { return arg; }
    Node* setArg(Node* newArg) { delete arg; arg = newArg; return this; }

private:
    Node* arg;
};

class InversionNode : public Arity1Node {
public:
    InversionNode(Node* init_arg) : arg(init_arg) {}

    ~InversionNode() {
        delete arg;
    }

    InversionNode* clone() const {
        return new InversionNode(arg->clone());
    }

    NodeType Type() const { return NodeType::Inversion; }

    Node* getArg() const { return arg; }
    Node* setArg(Node* newArg) { delete arg; arg = newArg; return this; }

private:
    Node* arg;
};

class ExpNode : public Node {
public:
    ExpNode(Node* init_base, Node* init_exp) : base(init_base), exponent(init_exp) {}

    ~ExpNode() {
        delete base;
        delete exponent;
    }

    ExpNode* clone() const {
        return new ExpNode(base->clone(), exponent->clone());
    }

    NodeType Type() const { return NodeType::Exponentiation; }

    unsigned arity() const { return 2; }

    bool hasPattern() const {
        return base->hasPattern() || exponent->hasPattern();
    }

    bool isEqual(Node const * const other) const {
        return (other->Type() == NodeType::Exponentiation) && base->isEqual(dynamic_cast<ExpNode const * const>(other)->base) && exponent->isEqual(dynamic_cast<ExpNode const * const>(other)->exponent);
    }

    Node* base;
    Node* exponent;
};

class LogNode : public Arity1Node {
public:
    LogNode(Node* init_arg) : arg(init_arg) {}

    ~LogNode() {
        delete arg;
    }

    LogNode* clone() const {
        return new LogNode(arg->clone());
    }

    NodeType Type() const { return NodeType::Logarithm; }

    Node* getArg() const { return arg; }
    Node* setArg(Node* newArg) { delete arg; arg = newArg; return this; }

private:
    Node* arg;
};

class SinNode : public Arity1Node {
public:
    SinNode(Node* init_arg) : arg(init_arg) {}

    ~SinNode() {
        delete arg;
    }

    SinNode* clone() const {
        return new SinNode(arg->clone());
    }

    NodeType Type() const { return NodeType::Sine; }

    Node* getArg() const { return arg; }
    Node* setArg(Node* newArg) { delete arg; arg = newArg; return this; }

private:
    Node* arg;
};

class CosNode : public Arity1Node {
public:
    CosNode(Node* init_arg) : arg(init_arg) {}

    ~CosNode() {
        delete arg;
    }

    CosNode* clone() const {
        return new CosNode(arg->clone());
    }

    NodeType Type() const { return NodeType::Cosine; }

    Node* getArg() const { return arg; }
    Node* setArg(Node* newArg) { delete arg; arg = newArg; return this; }

private:
    Node* arg;
};

class ArcSinNode : public Arity1Node {
public:
    ArcSinNode(Node* init_arg) : arg(init_arg) {}

    ~ArcSinNode() {
        delete arg;
    }

    ArcSinNode* clone() const {
        return new ArcSinNode(arg->clone());
    }

    NodeType Type() const { return NodeType::ArcSin; }

    Node* getArg() const { return arg; }
    Node* setArg(Node* newArg) { delete arg; arg = newArg; return this; }

private:
    Node* arg;
};

class ArcTanNode : public Arity1Node {
public:
    ArcTanNode(Node* init_arg) : arg(init_arg) {}

    ~ArcTanNode() {
        delete arg;
    }

    ArcTanNode* clone() const {
        return new ArcTanNode(arg->clone());
    }

    NodeType Type() const { return NodeType::ArcTan; }

    Node* getArg() const { return arg; }
    Node* setArg(Node* newArg) { delete arg; arg = newArg; return this; }

private:
    Node* arg;
};

class PatternMatchNode : public Node {
public:
    PatternMatchNode(int init_index) : index(init_index) {}

    PatternMatchNode* clone() const {
        return new PatternMatchNode(*this);
    }

    NodeType Type() const { return NodeType::PatternMatch; }

    unsigned arity() const { return -1; }

    bool hasPattern() const { return true; }

    bool isEqual(Node const * const other) const {
        return (other->Type() == NodeType::PatternMatch && dynamic_cast<PatternMatchNode const * const>(other)->getIndex() == index);
    }

    int getIndex() const { return index; }

private:
    int index;
};

class Expression {
public:
    Expression(Node* init_head) : head(init_head) {}

    friend void swap(Expression& first, Expression& second) {
        using std::swap;
        swap(first.head, second.head);
    }

    Expression(const Expression& other) {
        head = other.head->clone();
    }

    Expression& operator=(Expression other) {
        swap(*this, other);
        return *this;
    }

    Expression(Expression&& other) {
        head = nullptr;
        swap(*this, other);
    }

    ~Expression() {
        delete head;
    }

    Expression operator+(Expression g) {
        // This set will hold the addends in the head addition of our eventual expression
        collection_t newAddends;

        // Test if addition is already one of the operations in f and/or g
        if (head->Type() == NodeType::Addition) {
            for (auto x : dynamic_cast<AdditionNode*>(head)->addends) newAddends.insert(x);
        }
        else {
            newAddends.insert(head);
        }
        if (g.head->Type() == NodeType::Addition) {
            for (auto x : dynamic_cast<AdditionNode*>(g.head)->addends) newAddends.insert(x);
        }
        else {
            newAddends.insert(g.head);
        }

        AdditionNode* newHead = new AdditionNode(newAddends);

        return Expression(newHead);
    }

    Expression operator-() {
        NegationNode* newHead = new NegationNode(head);
        // Distribute negation over addition - not yet implemented
        //if (head->Type() == NodeType::Addition)

        return Expression(newHead);
    }
    Expression operator-(Expression g) {
        return *this + (-g);
    }
    Expression operator*(Expression g) {
        // This set will hold the addends in the head addition of our eventual expression
        collection_t newFactors;

        // Test if addition is already one of the operations in f and/or g
        if (head->Type() == NodeType::Multiplication) {
            for (auto x : dynamic_cast<ProductNode*>(head)->factors) newFactors.insert(x);
        }
        else {
            newFactors.insert(head);
        }
        if (g.head->Type() == NodeType::Multiplication) {
            for (auto x : dynamic_cast<ProductNode*>(g.head)->factors) newFactors.insert(x);
        }
        else {
            newFactors.insert(g.head);
        }

        ProductNode* newHead = new ProductNode(newFactors);

        return Expression(newHead);
    }

    bool isPattern() const {
        return head->hasPattern();
    }

    Node* head;
};

#endif /* expression_h */
