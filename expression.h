#include <cstdint>
#include <unordered_set>
using namespace std;

enum NodeType {     //Arity:
    ConstantQ,      //1R
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

    NodeType Type() const { return NodeType::Addition; }

    set<Node*> addends;
};

class ProductNode : public Node {
public:
    ProductNode(set<Node*> init_factors) : factors(init_factors) {}

    NodeType Type() const { return NodeType::Multiplication; }

    set<Node*> factors;
};

class NegationNode : public Node {
public:
    NegationNode(Node* init_arg) : arg(init_arg) {}

    NodeType Type() const { return NodeType::Negation; }

    Node* arg;
};

class InversionNode : public Node {
public:
    InversionNode(Node* init_arg) : arg(init_arg) {}

    NodeType Type() const { return NodeType::Inversion; }

    Node* arg;
};

class ExpNode : public Node {
public:
    ExpNode(Node* init_arg) : arg(init_arg) {}

    NodeType Type() const { return NodeType::Exponentiation; }

    Node* arg;
};

class LogNode : public Node {
public:
    LogNode(Node* init_arg) : arg(init_arg) {}

    NodeType Type() const { return NodeType::Logarithm; }

    Node* arg;
};

class SinNode : public Node {
public:
    SinNode(Node* init_arg) : arg(init_arg) {}

    NodeType Type() const { return NodeType::Sine; }

    Node* arg;
};

class CosNode : public Node {
public:
    CosNode(Node* init_arg) : arg(init_arg) {}

    NodeType Type() const { return NodeType::Cosine; }

    Node* arg;
};

class ArcSinNode : public Node {
public:
    ArcSinNode(Node* init_arg) : arg(init_arg) {}

    NodeType Type() const { return NodeType::ArcSin; }

    Node* arg;
};

class ArcTanNode : public Node {
public:
    ArcTanNode(Node* init_arg) : arg(init_arg) {}

    NodeType Type() const { return NodeType::ArcTan; }

    Node* arg;
};

class Expression {
public:
    Expression(Node* init_head) : head(init_head) {}

    Expression operator+(Expression g) {
        // This set will hold the addends in the head addition of our eventual expression
        set<Node*> addends;

        // Test if addition is already one of the operations in f and/or g
        if (head.Type() == NodeType::Addition) {
            for
        }
    }

    Node* head;
};
