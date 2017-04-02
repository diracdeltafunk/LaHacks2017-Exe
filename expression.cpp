#include "expression.h"

bool same_collection(collection_t a, collection_t b) {
    if (a.empty())
        return b.empty();
    auto x = *(a.begin());
    a.erase(a.begin());
    for (const auto& y : b) {
        if (x->isEqual(y)) {
            b.erase(y);
            return same_collection(a, b);
        }
    }
    return false;
}

void swap(Expression& first, Expression& second) {
    using std::swap;
    swap(first.head, second.head);
}

Expression::Expression(const Expression& other) {
    head = other.head->clone();
}

Expression& Expression::operator=(Expression other) {
    swap(*this, other);
    return *this;
}

/*Expression::Expression(Expression&& other) {
    head = nullptr;
    swap(*this, other);
}*/

Expression::~Expression() {
    delete head;
}

Expression Expression::operator+(const Expression& g) const {
    // This set will hold the addends in the head addition of our eventual expression
    collection_t newAddends;

    // Test if addition is already one of the operations in f and/or g
    if (head->Type() == NodeType::Addition) {
        for (const auto& x : dynamic_cast<AdditionNode*>(head)->addends) newAddends.insert(x->clone());
    }
    else {
        newAddends.insert(head->clone());
    }
    if (g.head->Type() == NodeType::Addition) {
        for (const auto& x : dynamic_cast<AdditionNode*>(g.head)->addends) newAddends.insert(x->clone());
    }
    else {
        newAddends.insert(g.head->clone());
    }

    return Expression(new AdditionNode(newAddends));
}

Expression Expression::operator-() const {
    NegationNode* newHead = new NegationNode(head);
    // Distribute negation over addition - not yet implemented
    //if (head->Type() == NodeType::Addition)

    return Expression(newHead);
}

Expression Expression::operator-(const Expression& g) const {
    return *this + (-g);
}

Expression Expression::operator*(const Expression& g) const {
    // This set will hold the addends in the head addition of our eventual expression
    collection_t newFactors;

    // Test if addition is already one of the operations in f and/or g
    if (head->Type() == NodeType::Multiplication) {
        for (const auto& x : dynamic_cast<ProductNode*>(head)->factors)
            newFactors.insert(x->clone());
    }
    else {
        newFactors.insert(head->clone());
    }
    if (g.head->Type() == NodeType::Multiplication) {
        for (const auto& x : dynamic_cast<ProductNode*>(g.head)->factors) newFactors.insert(x->clone());
    }
    else {
        newFactors.insert(g.head->clone());
    }

    return Expression(new ProductNode(newFactors));
}

bool Expression::operator==(const Expression& other) const {
    return head->isEqual(other.head);
}

bool Expression::operator!=(const Expression& other) const {
    return !(*this == other);
}

Expression Expression::operator/(const Expression& g) const {
    return *this * Expression(compose(new InversionNode(new IdentityNode()),g.head));
}

bool Expression::isPattern() const {
    return head->hasPattern();
}
