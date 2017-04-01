#include <cstdint>

class Rational {
public:
    Rational(int64_t, int64_t);
    double toDouble();
    Rational& operator+= (const Rational& r);
    Rational& operator-= (const Rational& r);
    Rational& operator*= (const Rational& r);
    Rational& operator/= (const Rational& r);
    const Rational& operator++() {
        numerator += denominator;
        return *this;
    }
    const Rational& operator--() {
        numerator -= denominator;
        return *this;
    }
private:
    int64_t numerator;
    int64_t denominator;
};
