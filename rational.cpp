#include "rational.h"
#include <iostream>

Rational::Rational(int64_t n, int64_t d) : numerator(n), denominator(d) {
    simplify();
}

double Rational::toDouble() const {
    return (double) numerator / (double) denominator;
}

Rational Rational::operator+(const Rational& other) const  {
    Rational result = *this;
    result.numerator = result.numerator*other.denominator + other.numerator*result.denominator;
    result.denominator *= other.denominator;
    result.simplify();
    return result;
}

Rational Rational::operator-(const Rational& other) const  {
    return *this + (-other);
}

Rational Rational::operator*(const Rational& other) const  {
    Rational result = *this;
    result.numerator *= other.numerator;
    result.denominator *= other.denominator;
    result.simplify();
    return result;
}

Rational Rational::operator/(const Rational& other) const  {
    Rational result = *this;
    result.numerator *= other.denominator;
    result.denominator *= other.numerator;
    result.simplify();
    return result;
}

Rational Rational::operator+= (const Rational& other) {
    numerator = numerator*other.denominator + other.numerator*denominator;
    denominator *= other.denominator;
    return *this;
}

Rational Rational::operator-= (const Rational& other) {
    return *this += (-other);
}

Rational Rational::operator*= (const Rational& other) {
    numerator *= other.numerator;
    denominator *= other.denominator;
    return *this;
}

Rational Rational::operator/= (const Rational& other) {
    numerator *= other.denominator;
    denominator *= other.numerator;
    return *this;
}

Rational& Rational::operator++() {
    numerator += denominator;
    simplify();
    return *this;
}

Rational& Rational::operator--() {
    numerator -= denominator;
    simplify();
    return *this;
}

Rational Rational::operator++(int) {
    Rational temp = *this;
    ++*this;
    return temp;
}

Rational Rational::operator--(int) {
    Rational temp = *this;
    --*this;
    return temp;
}

Rational Rational::operator-() const {
    Rational temp = *this;
    temp.numerator = -temp.numerator;
    return temp;
}

bool Rational::operator==(const Rational& other) const {
    return (numerator * other.denominator) == (other.numerator * denominator);
}

bool Rational::operator!=(const Rational& other) const {
    return !(*this == other);
}

bool Rational::operator<(const Rational& other) const {
    Rational difference = *this - other;
    difference.simplify();
    return difference.numerator < 0;
}

bool Rational::operator>(const Rational& other) const {
    return !(*this <= other);
}

bool Rational::operator<=(const Rational& other) const {
    return (*this < other) || (*this == other);
}

bool Rational::operator>=(const Rational& other) const {
    return !(*this < other);
}

int64_t gcd(int64_t a, int64_t b) {
    int64_t aa = std::abs(a);
    int64_t ab = std::abs(b);
    return ab == 0 ? aa : gcd(ab, aa % ab);
}

void Rational::simplify() {
    if (denominator == 0) {
        std::cerr << "YOU DIVIDED BY ZERO YOU TWAT" << std::endl;
        return;
    }
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
    int64_t g = gcd(numerator, denominator);
    numerator /= g;
    denominator /= g;
}
