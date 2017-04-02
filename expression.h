//
//  expression.h
//  LaHacks2017
//
//  Created by Kyle Hess on 4/1/17.
//  Copyright © 2017 Kyle Hess. All rights reserved.
//

#ifndef expression_h
#define expression_h

#include <set>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "directions.h"
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

bool same_collection(std::set<Node*> a, std::set<Node*> b);

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
        if (q.getNumerator() == 0)
            myStream << 0;
        else if (q.getDenominator() == 1)
            myStream << q.getNumerator();
        else
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
    AdditionNode(std::set<Node*> init_addends) : addends(init_addends) {}

    ~AdditionNode() {
        for (auto x : addends)
            delete x;
    }

    AdditionNode* clone() const {
        std::set<Node*> newAddends;
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

    std::set<Node*> addends;
};

class ProductNode : public Node {
public:
    ProductNode(std::set<Node*> init_factors) : factors(init_factors) {}

    ~ProductNode() {
        for (auto x : factors)
            delete x;
    }

    ProductNode* clone() const {
        std::set<Node*> newFactors;
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

    std::set<Node*> factors;
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

        if (base->Type() == NodeType::Addition || base->Type() == NodeType::Multiplication || base->Type() == NodeType::Exponentiation || base->Type() == NodeType::ConstantQ) {
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
        return "\\arctan\\left(" + arg->getString() + "\\right)";
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

// Testing for contant functions!
// Actually this just tests whether the tree contains an identity node
inline
bool isConstant(const Expression& f) {
    return !((f.head)->hasType(NodeType::Identity));
}
inline
bool isConstant(Node const * const f) {
    return !(f->hasType(NodeType::Identity));
}


// Composition!
inline
Node* compose(Node const * const, Node const * const);

inline
Expression compose(Expression f, Expression g) {
    return Expression(compose(f.head,g.head));
}

inline
Node* compose(Node const * const f, Node const * const g) {
    if (isConstant(f))
        return f->clone();
    if (f->Type() == NodeType::Identity)
        return g->clone();
    if (f->isStrictArity1()) {
        Arity1Node* newBaseFunc = dynamic_cast<Arity1Node*>(f->clone());
        Node* newArg = compose(newBaseFunc->getArg(), g);
        return newBaseFunc->setArg(newArg);
    }
    if (f->Type() == NodeType::Exponentiation) {
        const ExpNode* f_p = dynamic_cast<const ExpNode*>(f);
        Node* newBase = compose(f_p->base, g);
        Node* newExponent = compose(f_p->exponent, g);
        return new ExpNode(newBase, newExponent);
    }
    if (f->Type() == NodeType::Addition) {
        std::set<Node*> addends;
        for (auto x : dynamic_cast<const AdditionNode*>(f)->addends)
            addends.insert(compose(x,g));
        return new AdditionNode(addends);
    }
    if (f->Type() == NodeType::Multiplication) {
        std::set<Node*> factors;
        for (auto x : dynamic_cast<const ProductNode*>(f)->factors)
            factors.insert(compose(x,g));
        return new ProductNode(factors);
    }

    // If we get here something bad happened;
    Node* x = nullptr; *x;
    return x;
}

// Differentiation!
inline
Node* diff(Node const * const, DirNode& dirs);
inline
Node* diff(Node const * const);

inline
Expression diff(const Expression& g, DirNode& dirs) {
    return Expression(diff(g.head, dirs));
}
inline
Expression diff(const Expression& g) {
    return Expression(diff(g.head));
}

// Currently may introduce addition of zeroes from constants
// I could try fixing this up better with more logic later
// Also, it could have nested multiplications, which breaks associativity
// I could try fixing this too
// Also, I will implement keeping track of what instructions are done
// to differentiate so that we can do the backwards integration solution

// TODO: Make sure that this doesn't return any pointers involving original tree
//       Also check for memory leaks
//       Undo associativity breaking
//       Implement utility functions

// NOTE: This will most likely rapidly increase the complexity of expressions
//       **IF** you do not simplify expressions before passing them in.
//       I implemented some measures against ballooning simplified expressions
//       (i.e.- d/dx (e^x) = e^x and not d/dx (e^x) = log(e) * e^x),
//       but these will not work if your expression is not simplified beforehand!
//       For example, d/dx (x^log2)^3 = 3*(x^log2)^2*log2*(x^(log2-1))
//               but, d/dx x^(log2*3) = 3*log2*x^(log2*3-1)

// What to do with dirs:
// By default there is a dummy instruction
// Once we find out what the correct instruction should be, we replace it
// We push dummy children and push dirlists initialized to point to them
// when we have a subexpression to differentiate and we need to keep track
// of the rules for that
inline
Node* diff(Node const * const head, DirNode& dirs) {
    
    // Enforce that dirs is of the correct type
    if (!dirs.children.empty()) {
        int* x = nullptr; *x;
    }
    if (dirs.dir->Type() != DirType::DummyDir) {
        int* x = nullptr; *x;
    }
    
    // Make sure we're not differentiating a pattern
    if (head->hasPattern()) {
        int* x = nullptr; *x;
    }
    
    // Derivative of constants are zero (do this first so we don't spend
    // a long time doing chain and product rules just to get a bunch of zeroes)
    if (isConstant(head)) {
        dirs.set(new SpecialDir(SpecDirType::IntegralOfZero));
        return new RationalNode(Rational(0,1));
    }
    
    // Linearity
    // Checks if an argument is constant and if so just leaves it out
    // so that we don't have too many + 0's
    if (head->Type() == NodeType::Addition) {
        std::set<Node*> addends;
        for (auto x : dynamic_cast<const AdditionNode*>(head)->addends) {
            if (!isConstant(x)) {
                // Add how to integrate each component
                addends.insert(diff(x,*dirs.push()));
            }
        }
        
        // Set the direction to splitting the integral
        std::vector<Node*> args;
        for (auto x : addends) {
            args.push_back(x->clone());
        }
        dirs.set(new class SplitIntegral(args));
        
        return new AdditionNode(addends);
    }
    
    // Product rule
    // Leaves out additions of zero (i.e. c * x goes to c * 1 and not 0 * x + c * 1)
    if (head->Type() == NodeType::Multiplication) {
        
        // The way dir works for product rule is to randomly choose an element
        // in the resulting sum for applying integration by parts, which will
        // get the answer and have the rest of the integrals cancel out
        // These will be clones of the actual addends
        std::vector<Node*> dirAddends;
        // The function that was differentiated will be at the front
        std::vector<std::vector<Node*>> allTerms;
        
        std::set<Node*> addends;
        for (auto x : dynamic_cast<const ProductNode*>(head)->factors) {
            if (!isConstant(x)) {
                
                // NEW
                std::vector<Node*> dirfactors;
                
                std::set<Node*> factors;
                for (auto y : dynamic_cast<const ProductNode*>(head)->factors) {
                    if (x == y) {
                        
                        // NEW
                        dirfactors.push_back(y->clone());
                        std::swap(dirfactors[0],dirfactors[dirfactors.size() - 1]);
                        
                        if (y->Type() != NodeType::Identity)
                            factors.insert(diff(y));
                    }
                    else {
                        
                        // NEW
                        dirfactors.push_back(y->clone());
                        
                        factors.insert(y->clone());
                    }
                }
                ProductNode* nextAddend = new ProductNode(factors);
                
                // Here we are pushing the addend to the vector for the directions
                dirAddends.push_back(nextAddend->clone());
                allTerms.push_back(dirfactors);
                
                // And here we are pushing it for the differentiaion result
                addends.insert(nextAddend);
            }
        }
        
        // ******************************************************************
        // TODO: CHANGE THIS TO SOMETHING ELSE ONCE I REPLACE UNORDERED_SET
        // Choose a random distinguished element and do integration by parts on it
        
        dirs.set(new class SplitIntegral(dirAddends));
        std::vector<Node*> firstTermsMinus00 = allTerms[0];
        firstTermsMinus00.erase(firstTermsMinus00.begin());
        // *******************************************************************
        // CHANGE THIS WHEN DONE
        std::set<Node*> meldedStuff;
        for (int i = 0; i < firstTermsMinus00.size(); i++) {
            meldedStuff.insert(firstTermsMinus00[i]);
        }
        dirs.push(new class ByParts(new ProductNode(meldedStuff), allTerms[0][0]));
        
        // Add how to integrate dv
        diff(allTerms[0][0], *(dirs.children[0]->push()));
        
        // Prevent memory leaks by deleting unused nodes from allTerms
        // Make sure not to accidentally delete used nodes
        for (int i = 1; i < allTerms.size(); i++) {
            for (int j = 0; j < allTerms[i].size(); j++) {
                delete allTerms[i][j];
            }
        }
        
        return new AdditionNode(addends);
    }
    
    // Chain rule
    // If the argument is an identity we just apply one of the rules below
    // since then chain rule isn't needed
    // Right now it automatically chooses the outermost function to start with
    // (Just by the way diff is implemented recursively)
    // However, if we create integration problems we might want to have the
    // algorithm do things in different ways or at least store them as different u-subs and such.
    if (head->isStrictArity1() && dynamic_cast<const Arity1Node*>(head)->getArg()->Type() != NodeType::Identity) {
        std::set<Node*> factors;
        // Do chain rule on f(g(x))
        Node* g = (dynamic_cast<const Arity1Node*>(head)->getArg()->clone());
        Node* f = (head->clone());
        dynamic_cast<Arity1Node*>(f)->setArg(new IdentityNode());
        
        factors.insert(diff(g));
        // Used to make sure we don't have a memory leak
        Node* df = diff(f);
        factors.insert(compose(df,g));
        delete df;
        
        // Add U-sub direction
        // ************************************************
        // TODO: Make U-sub work in direction of letting u be innermost function,
        //       which should be more human-friendly
        dirs.set(new class Usub(g, f));
        dirs.push(new class DummyDir());
        dirs.push(new class DummyDir());
        delete diff(g, *dirs.children[0]);
        delete diff(f, *dirs.children[1]);
        
        return new ProductNode(factors);
    }
    
    // Exponentiation rule - this gets a bit ugly
    if (head->Type() == NodeType::Exponentiation) {
        const Node* base = dynamic_cast<const ExpNode*>(head)->base;
        const Node* exponent = dynamic_cast<const ExpNode*>(head)->exponent;
        
        // Check if exponentiation is of the form C^f(x)
        if (isConstant(base)) {
            std::set<Node*> factors;
            if (exponent->Type() != NodeType::Identity)
                factors.insert(diff(exponent));
            factors.insert(head->clone());
            // Only multiply by log of base if base is not e
            // This doesn't catch stupid expressions, like, (e^3)^x
            if (base->Type() != NodeType::ConstantE) {
                factors.insert(new LogNode(base->clone()));
            }
            
            // Add U-sub direction
            // ************************************************
            // TODO: Make U-sub work in direction of letting u be innermost function,
            //       which should be more human-friendly
            Node* f = head->clone();
            delete dynamic_cast<ExpNode*>(f)->exponent;
            dynamic_cast<ExpNode*>(f)->exponent = new IdentityNode();
            dirs.set(new class Usub(exponent->clone(), f));
            dirs.push(new class DummyDir());
            dirs.push(new class DummyDir());
            delete diff(exponent, *dirs.children[0]);
            delete diff(f, *dirs.children[1]);
            
            return new ProductNode(factors);
        }
        
        // Check if exponentiation is of the form f(x)^C
        // This could introduce expressions of the form a/b * b * x
        if (isConstant(exponent)) {
            std::set<Node*> factors;
            factors.insert(exponent->clone());
            
            // Do special stuff if the exponent is a rational number
            if (exponent->Type() == NodeType::ConstantQ) {
                Rational newExponent = dynamic_cast<const RationalNode*>(exponent)->getNumber() - Rational(1,1);
                factors.insert(new ExpNode(base->clone(), new RationalNode(newExponent)));
            }
            else {
                std::set<Node*> addends;
                addends.insert(exponent->clone());
                addends.insert(new NegationNode(new RationalNode(Rational(1,1))));
                factors.insert(new ExpNode(base->clone(), new AdditionNode(addends)));
            }
            
            // Add U-sub direction
            // ************************************************
            // TODO: Make U-sub work in direction of letting u be innermost function,
            //       which should be more human-friendly
            Node* f = head->clone();
            delete dynamic_cast<ExpNode*>(f)->base;
            dynamic_cast<ExpNode*>(f)->base = new IdentityNode();
            dirs.set(new class Usub(base->clone(), f));
            dirs.push(new class DummyDir());
            dirs.push(new class DummyDir());
            delete diff(base, *dirs.children[0]);
            delete diff(f, *dirs.children[1]);
            
            return new ProductNode(factors);
        }
        
        // Otherwise we have to get ugly
        std::set<Node*> addends;
        // factors1 is x^y*lnx*dy
        std::set<Node*> factors1;
        factors1.insert(head->clone());
        factors1.insert(new LogNode(base->clone()));
        if (exponent->Type() != NodeType::Identity)
            factors1.insert(diff(exponent->clone()));
        // factors2 is x^y*y/x*dx
        std::set<Node*> factors2;
        factors2.insert(head->clone());
        factors2.insert(exponent->clone());
        factors2.insert(new InversionNode(base->clone()));
        if (base->Type() != NodeType::Identity)
            factors2.insert(diff(base));
        // Now add them together
        addends.insert(new ProductNode(factors1));
        addends.insert(new ProductNode(factors2));
        
        // Add U-sub direction
        // ************************************************
        // TODO: Make the exponent rules & differentiation better
        Node* f = new ExpNode(new ENode(), new IdentityNode);
        Node* copyOfBase = base->clone();
        Node* logOfBase = new LogNode(copyOfBase);
        Node* copyOfExponent = exponent->clone();
        Node* g = (Expression(logOfBase) * Expression(copyOfExponent)).head;
        
        dirs.set(new class RewriteExpToUnary(head->clone(),compose(f,g)));
        dirs.push(new class Usub(g, f));
        dirs.push(new class RewriteExpToBinary(head->clone(),compose(f,g)));
        dirs.children[0]->push();
        dirs.children[0]->push();
        delete diff(g, *dirs.children[0]->children[0]);
        delete diff(f, *dirs.children[0]->children[1]);
        // Delete pointers to prevent memory leaks
        delete copyOfBase;
        delete logOfBase;
        delete copyOfExponent;
        
        return new AdditionNode(addends);
    }
    
    // If we get here, then head is either of the form f(x) for some elementary function f
    // Or head is just an identity node
    // (which only happens if our whole expression was just x)
    if (head->Type() == NodeType::Negation) {
        // Returns -1
        
        dirs.set(new SpecialDir(SpecDirType::IntegralOfMinusOne));
        
        return new RationalNode(Rational(-1, 1));
    }
    if (head->Type() == NodeType::Inversion) {
        // Returns -1/x^2
        
        dirs.set(new SpecialDir(SpecDirType::InversionIntegral));
        
        return new NegationNode(new InversionNode(new ExpNode(new IdentityNode(), new RationalNode(Rational(2,1)))));
    }
    if (head->Type() == NodeType::Logarithm) {
        // Returns 1/x
        
        dirs.set(new SpecialDir(SpecDirType::LogIntegral));
        
        return new InversionNode(new IdentityNode);
    }
    if (head->Type() == NodeType::Sine) {
        // Returns cos(x)
        
        dirs.set(new SpecialDir(SpecDirType::SineIntegral));
        
        return new CosNode(new IdentityNode());
    }
    if (head->Type() == NodeType::Cosine) {
        // Returns -x
        
        dirs.set(new SpecialDir(SpecDirType::CosineIntegral));
        
        return new NegationNode(new SinNode(new IdentityNode()));
    }
    if (head->Type() == NodeType::ArcSin) {
        // Returns 1/(1-x^2)^0.5
        
        dirs.set(new SpecialDir(SpecDirType::ArcSinIntegral));
        
        std::set<Node*> addends;
        addends.insert(new RationalNode(Rational(1,1)));
        addends.insert(new NegationNode(new ExpNode(new IdentityNode(), new RationalNode(Rational(2,1)))));
        return new InversionNode(new ExpNode(new AdditionNode(addends), new RationalNode(Rational(1,2))));
    }
    if (head->Type() == NodeType::ArcTan) {
        // Returns 1/(1 + x^2)
        
        dirs.set(new SpecialDir(SpecDirType::ArcTanIntegral));
        
        std::set<Node*> addends;
        addends.insert(new RationalNode(Rational(1,1)));
        addends.insert(new ExpNode(new IdentityNode(), new RationalNode(Rational(2,1))));
        return new InversionNode(new AdditionNode(addends));
    }
    if (head->Type() == NodeType::Identity) {
        // Returns 1
        
        dirs.set(new SpecialDir(SpecDirType::IntegralOfPlusOne));
        
        return new RationalNode(Rational(1,1));
    }
    
    // If we get here, then I missed a case and something bad happened
    Node* x = nullptr; *x;
    return x;
}
inline
Node* diff(Node const * const head) {
    DirNode dirs(nullptr, new class DummyDir());
    return diff(head, dirs);
}



// Printing!!
inline
std::ostream& operator<<(std::ostream& os, Expression f) {
    os << (f.head)->getString();
    return os;
}

#endif /* expression_h */
