//
//  directions.h
//  Integrations
//
//  Created by Kyle Hess on 4/1/17.
//  Copyright © 2017 Kyle Hess. All rights reserved.
//

#ifndef directions_h
#define directions_h

#include <vector>
#include <string>

class Expression;
class Node;

// Arithmetic rules not yet implemented,
// so those steps aren't recorded
enum DirType {
    DummyDir = -1,
    RewriteExpToUnary,
    RewriteExpToBinary,
    Usub,
    ByParts,
    SplitIntegral,
    Special
};

class Direction {
public:
    virtual ~Direction() {}
    
    virtual DirType Type() = 0;
private:
};

// For when you need a dummy direction
class DummyDir : public Direction {
public:
    
    virtual DirType Type() { return DirType::DummyDir; }
private:
};

// Says to rewrite x^y as e^(lnx * y)
// Contains the proper Usub and the RewriteExpToBinary afterwards
// arg1 is x^y, arg2 is e^(lnx * y)
class RewriteExpToUnary : public Direction {
public:
    RewriteExpToUnary(Node* init_arg1, Node* init_arg2) : arg1(init_arg1), arg2(init_arg2) {}
    
    virtual DirType Type() { return DirType::RewriteExpToUnary; }
    
    Node* arg1;
    Node* arg2;
private:
};

// Says to rewrite e^(lnx * y) as x^y
class RewriteExpToBinary : public Direction {
public:
    RewriteExpToBinary(Node* init_arg1, Node* init_arg2) : arg1(init_arg1), arg2(init_arg2) {}
    
    virtual DirType Type() { return DirType::RewriteExpToBinary; }
    
    Node* arg1;
    Node* arg2;
private:
};

// Nodes which have Usub directions contain as their children
// How to integrate u'
// How to integrate f(u)du
// - Not yet implemented
//**********************************************************
// IMPLEMENT THE ABOVE AFTER FIXING UP CHAIN RULE TO DIFFERENTIATE RIGHT
class Usub : public Direction {
public:
    Usub(Node* init_u, Node* init_f) : u(init_u), f(init_f) {}
    
    DirType Type() { return DirType::Usub; }
    
    Node* u;
    Node* f;
private:
    
};

// Nodes which have ByParts directions contain as their children
// How to integrate dv
class ByParts : public Direction {
public:
    ByParts(Node* init_u, Node* init_v) : u(init_u), v(init_v) {}
    
    DirType Type() { return DirType::ByParts; }
    
    Node* u;
    Node* v;
private:
};

// Nodes which have SplitIntegral directions contain as their children
// How to integrate each component function (if came from addition)
// How to integrate specific component function (if came from product rule)
class SplitIntegral : public Direction {
public:
    SplitIntegral(std::vector<Node*> init_args) : args(init_args) {}
    ~SplitIntegral();
    
    DirType Type() { return DirType::SplitIntegral; }
    
    std::vector<Node*> args;
private:
};


enum SpecDirType {
    IntegralOfZero,
    IntegralOfPlusOne,
    IntegralOfMinusOne,
    InversionIntegral,
    LogIntegral,
    SineIntegral,
    CosineIntegral,
    ArcSinIntegral,
    ArcTanIntegral
};

class SpecialDir : public Direction {
public:
    
    SpecialDir(SpecDirType init_rule) : rule(init_rule) {}
    
    DirType Type() { return DirType::Special; }
    SpecDirType SpecType() { return rule; }
    
    SpecDirType rule;
};

class DirNode {
public:
    DirNode(DirNode* init_parent, Direction* init_dir) : parent(init_parent), dir(init_dir) {}
    ~DirNode() {
        for (int i = 0; i < children.size(); i++) {
            delete children[i];
        }
        delete dir;
    }
    
    void clear() {
        for (int i = 0; i < children.size(); i++) {
            delete children[i];
        }
        children.clear();
        set(new class DummyDir);
    }
    
    // Returns pushed child node
    DirNode* push() {
        return push(new class DummyDir());
    }
    DirNode* push(Direction* dir) {
        DirNode* newNode = new DirNode(this, dir);
        children.push_back(newNode);
        return newNode;
    }
    
    // Sets the root to have the given direction
    void set(Direction* newDir) {
        delete dir;
        dir = newDir;
    }
    
    std::string getSolution(Node const * const Integral, int depth = 0, int listNo = 0);
    
    std::vector<DirNode*> children;
    DirNode* parent;
    
    Direction* dir;
};


#endif /* directions_h */






























