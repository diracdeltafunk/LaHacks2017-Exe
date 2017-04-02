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
#include <sstream>
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
    virtual ~Node() {};
    virtual Node* clone() const = 0;
    virtual NodeType Type() const = 0;
    virtual unsigned arity() const = 0;
    virtual bool isStrictArity0() const { return false; }
    virtual bool isStrictArity1() const { return false; }
    virtual bool hasType(const NodeType&) const = 0;
    bool hasPattern() const { return hasType(NodeType::PatternMatch); }
    virtual bool isEqual(Node const * const) const = 0;
    bool operator==(const Node& other) const { return other.isEqual(this); }
    // Gives an expression as a string
    virtual std::string getString() const = 0;
};

typedef std::unordered_set<Node*> collection_t;

bool same_collection(collection_t a, collection_t b);

class Arity0Node : public Node {
public:
    unsigned arity() const { return 0; }
    bool isStrictArity0() const { return true; }
    bool hasPattern() const { return false; }
    bool hasType(const NodeType& t) const { return t == Type(); }
    virtual std::string getString() const = 0;
};

class Arity1Node : public Node {
public:
    unsigned arity() const { return 1; }
    bool isStrictArity1() const { return true; }
    virtual Node* getArg() const = 0;
    virtual Node* setArg(Node* newArg) = 0;
    bool hasPattern() const { return getArg()->hasPattern(); }
    bool isEqual(Node const * const other) const {
        return (other->Type() == this->Type()) && (getArg()->isEqual(dynamic_cast<Arity1Node const * const>(other)->getArg()));
    }
    bool hasType(const NodeType& t) const {
        return (t == Type()) || (getArg()->hasType(t));
    }
    virtual std::string getString() const = 0;
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
    virtual std::string getString() const {
        std::ostringstream myStream;
        myStream << "\\frac{" << q.getNumerator() << "}{" << q.getDenominator() << "}";
        return myStream.str();
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

    virtual std::string getString() const { return "\\pi"; }
};

class ENode : public Arity0Node {
public:
    NodeType Type() const { return NodeType::ConstantE; }

    ENode* clone() const {
        return new ENode;
    }

    bool isEqual(Node const * const other) const {
        return other->Type() == NodeType::ConstantE;
    }

    virtual std::string getString() const { return "e"; }
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

    virtual std::string getString() const { return "x"; }
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

    bool hasType(const NodeType& t) const {
        if (t == NodeType::Addition)
            return true;
        for (const auto& a : addends) {
            if (a->hasType(t))
                return true;
        }
        return false;
    }

    bool isEqual(Node const * const other) const {
        if ((other->Type() != NodeType::Addition) || (arity() != other->arity()))
            return false;
        return same_collection(addends, dynamic_cast<AdditionNode const * const>(other)->addends);
    }

    virtual std::string getString() const {
        std::ostringstream myStream;
        bool firstElement = true;

        for (auto x : addends) {
            if (!firstElement)
                myStream << " + ";
            else firstElement = false;

            if (x->Type() == NodeType::Addition || x->Type() == NodeType::Multiplication) {
                myStream << "\\left(" + x->getString() << "\\right)";
            }
            else {
                myStream << x->getString();
            }
        }

        return myStream.str();
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

    bool hasType(const NodeType& t) const {
        if (t == NodeType::Multiplication)
            return true;
        for (const auto& a : factors) {
            if (a->hasType(t))
                return true;
        }
        return false;
    }

    bool isEqual(Node const * const other) const {
        if ((other->Type() != NodeType::Multiplication) || (arity() != other->arity()))
            return false;
        return same_collection(factors, dynamic_cast<ProductNode const * const>(other)->factors);
    }

    virtual std::string getString() const {
        std::ostringstream myStream;
        bool firstElement = true;

        for (auto x : factors) {
            if (!firstElement)
                myStream << " \\cdot ";
            else firstElement = false;

            if (x->Type() == NodeType::Addition || x->Type() == NodeType::Multiplication) {
                myStream << "\\left(" + x->getString() << "\\right)";
            }
            else {
                myStream << x->getString();
            }
        }

        return myStream.str();
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

    virtual std::string getString() const {
        if (arg->Type() == NodeType::Addition || arg->Type() == NodeType::Multiplication) {
            return "-\\left(" + arg->getString() + "\\right)";
        }
        else {
            return "-" + arg->getString();
        }
    }

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

    virtual std::string getString() const {
        return "\\frac{1}{" + arg->getString() + "}";
    }

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

    bool hasType(const NodeType& t) const {
        return (t == NodeType::Exponentiation) || base->hasType(t) || exponent->hasType(t);
    }

    bool isEqual(Node const * const other) const {
        return (other->Type() == NodeType::Exponentiation) && base->isEqual(dynamic_cast<ExpNode const * const>(other)->base) && exponent->isEqual(dynamic_cast<ExpNode const * const>(other)->exponent);
    }

    virtual std::string getString() const {
        std::ostringstream myStream;

        if (base->Type() == NodeType::Addition || base->Type() == NodeType::Multiplication || base->Type() == NodeType::Exponentiation) {
            myStream << "\\left(" + base->getString() + "\\right)";
        }
        else {
            myStream << base->getString();
        }

        myStream << "^";
        myStream << "{" + exponent->getString() + "}";

        return myStream.str();
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

    virtual std::string getString() const {
        return "\\log\\left(" + arg->getString() + "\\right)";
    }

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

    virtual std::string getString() const {
        return "\\sin\\left(" + arg->getString() + "\\right)";
    }

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

    virtual std::string getString() const {
        return "\\cos\\left(" + arg->getString() + "\\right)";
    }

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

    virtual std::string getString() const {
        return "\\arcsin\\left(" + arg->getString() + "\\right)";
    }

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

    virtual std::string getString() const {
        return "\\arctan(" + arg->getString() + ")";
    }

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

    bool hasType(const NodeType& t) const {
        return t == NodeType::PatternMatch;
    }

    bool isEqual(Node const * const other) const {
        return (other->Type() == NodeType::PatternMatch && dynamic_cast<PatternMatchNode const * const>(other)->getIndex() == index);
    }

    int getIndex() const { return index; }

    virtual std::string getString() const {
        return "WHAT ARE YOU DOING YOU CAN'T PRINT PATTERN NODES";
    }

private:
    int index;
};

class Expression {
public:
    Expression(Node* init_head) : head(init_head) {}

    friend void swap(Expression& first, Expression& second);

    Expression(const Expression& other);

    Expression& operator=(Expression other);

    Expression(Expression&& other);

    ~Expression();

    Expression operator+(const Expression&) const;

    Expression operator-() const;

    Expression operator-(const Expression&) const;

    Expression operator*(const Expression&) const;

    Expression operator/(const Expression& g) const;

    bool operator==(const Expression&) const;

    bool operator!=(const Expression&) const;

    bool isPattern() const;

    Node* head;
};

// Printing!!
inline
std::ostream& operator<<(std::ostream& os, Expression f) {
    os << (f.head)->getString();
    return os;
}

#endif /* expression_h */
