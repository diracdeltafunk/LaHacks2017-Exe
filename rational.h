#ifndef rational_h
#define rational_h

#include <cstdint>

class Rational {
public:
    Rational(int64_t, int64_t);
    double toDouble() const;
    int64_t getNumerator() const    { return numerator; }
    int64_t getDenominator() const  { return denominator; }
    // Arithmetic
    Rational operator+(const Rational&) const;
    Rational operator-(const Rational&) const;
    Rational operator*(const Rational&) const;
    Rational operator/(const Rational&) const;
    // Compound Assignments
    Rational operator+= (const Rational&);
    Rational operator-= (const Rational&);
    Rational operator*= (const Rational&);
    Rational operator/= (const Rational&);
    // Prefix Increment and Decrement
    Rational& operator++();
    Rational& operator--();
    // Postfix Incremenet and Decrement
    Rational operator++(int);
    Rational operator--(int);
    // Unary Minus
    Rational operator-() const;
    // Comparison
    bool operator==(const Rational&) const;
    bool operator!=(const Rational&) const;
    bool operator<(const Rational&) const;
    bool operator>(const Rational&) const;
    bool operator<=(const Rational&) const;
    bool operator>=(const Rational&) const;
private:
    int64_t numerator;
    int64_t denominator;
    void simplify();
};

#endif
