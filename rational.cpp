#include "rational.h"
#include <numeric>

Rational::Rational(int64_t n, int64_t d) {
    int64_t g = std::gcd(n,d);
    numerator = n / g;
    denominator = d / g;
}

double Rational::toDouble() {
    return (double) numerator / (double) denominator;
}
