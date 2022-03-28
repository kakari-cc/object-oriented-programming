#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>

class Rational {
    int numerator, denominator;
    void normalize();
    
public:
    Rational(int numerator = 0, int denominator = 1);
    friend std::ostream& operator<<(std::ostream& os, const Rational& rhs);
    friend std::istream& operator>>(std::istream& is, Rational& rhs);
    friend bool operator==(const Rational& lhs, const Rational& rhs);
    friend bool operator<(const Rational& lhs, const Rational& rhs);
    Rational& operator+=(const Rational& rhs);
    Rational& operator++();
    Rational operator++(int dummy);
    explicit operator bool() const;
};

Rational& operator--(Rational& rhs);
Rational operator--(Rational& rhs, int dummy);
Rational operator+(const Rational& lhs, const Rational& rhs);
bool operator!=(const Rational& lhs, const Rational& rhs);
bool operator<=(const Rational& lhs, const Rational& rhs);
bool operator>(const Rational& lhs, const Rational& rhs);
bool operator>=(const Rational& lhs, const Rational& rhs);

#endif
