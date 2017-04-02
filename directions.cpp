//
//  directions.cpp
//  Integrations
//
//  Created by Kyle Hess on 4/1/17.
//  Copyright © 2017 Kyle Hess. All rights reserved.
//

#include "directions.h"
#include "expression.h"

SplitIntegral::~SplitIntegral() {
    for (int i = 0; i < args.size(); i++) {
        delete args[i];
    }
}

std::string DirNode::getSolution(Node const * const Integral, int depth, int listNo) {
    
    // ****************************************
    // ADD IN +C'S!!!!
    
    std::string tabs = "\n\n";
    for (int i = 0; i < depth; i++) {
        tabs += "$\\;\\;\\;\\;\\;\\;$";
    }
    
    
    if (dir->Type() == DirType::DummyDir) {
        int* x = nullptr; *x;
        
        return "Something bad happened.";
    }
    if (dir->Type() == DirType::RewriteExpToUnary) {
        Node* arg1 = dynamic_cast<class RewriteExpToUnary*>(dir)->arg1;
        Node* arg2 = dynamic_cast<class RewriteExpToUnary*>(dir)->arg2;
        return tabs + "Rewrite the exponent, $" + arg1->getString() + "$, as $" + arg2->getString() + "$ then:\n" + children[0]->getSolution(dynamic_cast<ExpNode*>(arg2)->exponent, depth + 1) + children[1]->getSolution(Integral, depth);
    }
    if (dir->Type() == DirType::RewriteExpToBinary) {
        Node* arg1 = dynamic_cast<class RewriteExpToBinary*>(dir)->arg1;
        Node* arg2 = dynamic_cast<class RewriteExpToBinary*>(dir)->arg2;
        return tabs + "Now undo the rewrite you made earlier and rewrite the exponent, $" + arg2->getString() + "$, back as $" + arg1->getString() + "$ to finish integrating $" + Integral->getString() + "=" + arg1->getString() + "$.\n";
    }
    if (dir->Type() == DirType::Usub) {
        Node* u = dynamic_cast<class Usub*>(dir)->u;
        Node* f = dynamic_cast<class Usub*>(dir)->f;
        Node* du = diff(u);
        Node* df = diff(f);
        Node* comp = compose(df,u);
        // Create an expression from du & df so that it is destroyed later
        Expression holder1(u);
        Expression holder2(f);
        Expression holder3(comp);
        return tabs + "Integrate only $" + du->getString() + "$ by doing:\n" + children[0]->getSolution(du,depth+1) + tabs + "Now that we learned that the integral of $" + du->getString() + "$ is $" + u->getString() + "$ we can use chain rule to reduce this to the problem of finding the integral of $" + df->getString() + "$, which, to do, you only need to do this:\n" + children[1]->getSolution(df,depth+1) + tabs + "Since we've proven $\\int " + Integral->getString() + "\\; \\mathrm{d}x = \\int " + comp->getString() + "\\; \\mathrm{d}x$ and $\\int " + comp->getString() + "\\; \\mathrm{d}x = \\int " + f->getString() + "\\; \\mathrm{d}x$ we know that $\\int " + Integral->getString() + "\\; \\mathrm{d}x = \\int " + comp->getString() + "\\; \\mathrm{d}x$.\n";
    }
    if (dir->Type() == DirType::ByParts) {
        Node* u = dynamic_cast<class ByParts*>(dir)->u;
        Node* v = dynamic_cast<class ByParts*>(dir)->v;
        Node* du = diff(u);
        Node* dv = diff(v);
        
        // Protect against memory leaks
        Expression holder1(dv);
        
        return tabs + "Use integration by parts using $u=" + u->getString() + ", dv=" + dv->getString() + "$. To find $\\int " + dv->getString() + "\\; \\mathrm{d}x$ follow these steps:\n" + children[0]->getSolution(dv,depth+1) + tabs + "Thus, we get that $\\int " + Integral->getString() + "\\; \\mathrm{d}x = (" + u->getString() + ")(" + v->getString() + ")-\\int \\left(" + du->getString() + "\\right) \\left(" + v->getString() + "\\right) \\; \\mathrm{d}x$.\n";
    }
    if (dir->Type() == DirType::SplitIntegral) {
        std::string splitUpIntegral = "";
        std::vector<Node*> addends = dynamic_cast<class SplitIntegral*>(dir)->args;
        for (int i = 0; i < addends.size(); i++) {
            splitUpIntegral += "\\int " + addends[i]->getString() + "\\; \\mathrm{d}x";
            if (i != addends.size() - 1) {
                splitUpIntegral += " + ";
            }
        }
        if (children[0]->dir->Type() != ByParts) {
            std::string nextInstructions;
            for (int i = 0; i < children.size(); i++) {
                nextInstructions += children[i]->getSolution(addends[i],depth+1);
            }
            return tabs + "Just split up this integral into separate integrals using the linearity properties of the integral. Now follow these steps to solve each individual integral:\n" + nextInstructions;
        }
        else {
            return tabs + "Just split up this integral into separate integrals using the linearity properties of the integral to get the expression $" + splitUpIntegral + "$. Next, focus on the first integral.\n" + children[0]->getSolution(addends[0],depth+1) + tabs + "Notice that the part of the integral that is $-\\int vdu\\; \\mathrm{d}x$ cancels with the rest of the sum to give us just the part which is $uv$, which is our answer.";
        }
    }
    
    if (dir->Type() == DirType::Special) {
        SpecDirType IntegralType = dynamic_cast<SpecialDir*>(dir)->SpecType();
        
        if (IntegralType == SpecDirType::IntegralOfZero) {
            return tabs + "Use the rule that the integral of zero is C.\n";
        }
        if (IntegralType == SpecDirType::IntegralOfPlusOne) {
            return tabs + "Use the rule that the integral of $+1$ is $x+C$.\n";
        }
        if (IntegralType == SpecDirType::IntegralOfMinusOne) {
            return tabs + "Use the rule that the integral of $-1$ is $-x+C$.\n";
        }
        if (IntegralType == SpecDirType::InversionIntegral) {
            return tabs + "Use the rule that the integral of $-\\frac{1}{x^2}$ is $\\frac{1}{x}+C$.\n";
        }
        if (IntegralType == SpecDirType::LogIntegral) {
            return tabs + "Use the rule that the integral of $\\frac{1}{x}$ is $\\log(x)+C$.\n";
        }
        if (IntegralType == SpecDirType::SineIntegral) {
            return tabs + "Use the rule that the integral of $\\cos(x)$ is $\\sin(x)+C$.\n";
        }
        if (IntegralType == SpecDirType::CosineIntegral) {
            return tabs + "Use the rule that the integral of $-\\sin(x)$ is $\\cos(x)+C$.\n";
        }
        if (IntegralType == SpecDirType::ArcSinIntegral) {
            return tabs + "Use the rule that the integral of $\\frac{1}{\\left(1-x^2\\right)^{frac{1}{2}}}$ is $\\arcsin(x)+C$.\n";
        }
        if (IntegralType == SpecDirType::ArcTanIntegral) {
            return tabs + "Use the rule that the integral of $\\frac{1}{1+x^2}$ is $\\arctan(x)+C$.\n";
        }
    }
    
    // If we get here then there was a problem
    int* x = nullptr; *x;
    
    return "";
}




























