//
//  expression.h
//  Integrations
//
//  Created by Kyle Hess on 4/1/17.
//  Copyright © 2017 Kyle Hess. All rights reserved.
//

#ifndef expression_h
#define expression_h

#include <cstdint>
#include <unordered_set>
using namespace std;

enum NodeType {     //Arity:
    ConstantQ,      //1
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
    ArcTan          //1
};

class Node {
public:
    virtual ~Node() = 0;
    virtual NodeType Type() const = 0;
};

class RationalNode : public Node {
public:
    RationalNode(int init_num, int init_den) : num(init_num), den(init_den) {}

    NodeType Type() const { return NodeType::ConstantQ; }

    // Overload == operator
    bool operator==(RationalNode q) {
        return (num * q.den) == (den * q.num);
    }

    int num;
    int den;
};

class PiNode : public Node {
public:
    NodeType Type() const { return NodeType::ConstantPi; }
};

class ENode : public Node {
public:
    NodeType Type() const { return NodeType::ConstantE; }
};

class IdentityNode : public Node {
public:
    NodeType Type() const { return NodeType::Identity; }
};

class AdditionNode : public Node {
public:
    AdditionNode(unordered_set<Node*> init_addends) : addends(init_addends) {}

    ~AdditionNode() {
        for (auto x : addends)
            delete x;
    }

    NodeType Type() const { return NodeType::Addition; }

    unordered_set<Node*> addends;
};

class ProductNode : public Node {
public:
    ProductNode(unordered_set<Node*> init_factors) : factors(init_factors) {}

    ~ProductNode() {
        for (auto x : factors)
            delete x;
    }

    NodeType Type() const { return NodeType::Multiplication; }

    unordered_set<Node*> factors;
};

class NegationNode : public Node {
public:
    NegationNode(Node* init_arg) : arg(init_arg) {}

    ~NegationNode() {
        delete arg;
    }

    NodeType Type() const { return NodeType::Negation; }

    Node* arg;
};

class InversionNode : public Node {
public:
    InversionNode(Node* init_arg) : arg(init_arg) {}

    ~InversionNode() {
        delete arg;
    }

    NodeType Type() const { return NodeType::Inversion; }

    Node* arg;
};

class ExpNode : public Node {
public:
    ExpNode(Node* init_arg) : arg(init_arg) {}

    ~ExpNode() {
        delete arg;
    }

    NodeType Type() const { return NodeType::Exponentiation; }

    Node* arg;
};

class LogNode : public Node {
public:
    LogNode(Node* init_arg) : arg(init_arg) {}

    ~LogNode() {
        delete arg;
    }

    NodeType Type() const { return NodeType::Logarithm; }

    Node* arg;
};

class SinNode : public Node {
public:
    SinNode(Node* init_arg) : arg(init_arg) {}

    ~SinNode() {
        delete arg;
    }

    NodeType Type() const { return NodeType::Sine; }

    Node* arg;
};

class CosNode : public Node {
public:
    CosNode(Node* init_arg) : arg(init_arg) {}

    ~CosNode() {
        delete arg;
    }

    NodeType Type() const { return NodeType::Cosine; }

    Node* arg;
};

class ArcSinNode : public Node {
public:
    ArcSinNode(Node* init_arg) : arg(init_arg) {}

    ~ArcSinNode() {
        delete arg;
    }

    NodeType Type() const { return NodeType::ArcSin; }

    Node* arg;
};

class ArcTanNode : public Node {
public:
    ArcTanNode(Node* init_arg) : arg(init_arg) {}

    ~ArcTanNode() {
        delete arg;
    }

    NodeType Type() const { return NodeType::ArcTan; }

    Node* arg;
};

class Expression {
public:
    Expression(Node* init_head) : head(init_head) {}

    Expression(const Expression& other) {
        head = new Node;
        *head = *other.head;
    }

    Expression& operator=(const Expression& other) {
        //writing copy-assignment
    }

    ~Expression() {
        delete head;
    }

    Expression operator+(Expression g) {
        // This set will hold the addends in the head addition of our eventual expression
        unordered_set<Node*> newAddends;

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
        unordered_set<Node*> newFactors;

        // Test if addition is already one of the operations in f and/or g
        if (head->Type() == NodeType::Multiplication) {
            for (auto x : dynamic_cast<ProductNode*>(head)->factors) newFactors.insert(x);
        }
        else {
            newFactors.insert(head);
        }
        if (g.head->Type() == NodeType::Addition) {
            for (auto x : dynamic_cast<ProductNode*>(g.head)->factors) newFactors.insert(x);
        }
        else {
            newFactors.insert(g.head);
        }

        ProductNode* newHead = new ProductNode(newFactors);

        return Expression(newHead);
    }

    Node* head;
};



#endif /* expression_h */
