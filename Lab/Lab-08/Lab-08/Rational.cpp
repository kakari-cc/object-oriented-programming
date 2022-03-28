#include <iostream>
#include "Rational.h"

using namespace std;

int greatestCommonDivisor(int x, int y) {
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

void Rational::normalize() {
    int gcd = greatestCommonDivisor(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;
    if(denominator < 0) {
        numerator *= -1;
        denominator *= -1;
    }
}

Rational::Rational(int numerator, int denominator)
    : numerator(numerator)
    , denominator(denominator)
{
    normalize();
};

ostream& operator<<(ostream& os, const Rational& rhs) {
    return os << rhs.numerator << "/" << rhs.denominator;
}

istream& operator>>(istream& is, Rational& rhs) {
    char slash;
//    scanf("%d/%d", &rhs.numerator, &rhs.denominator);
    is >> rhs.numerator >> slash >> rhs.denominator;
    if(rhs.denominator == 0) {
        cerr << "(!) Denominator Cannot Be Zero" << endl;
        return is;
    }
    rhs.normalize();
    return is;
}

Rational& Rational::operator+=(const Rational& rhs) {
    numerator = (numerator * rhs.denominator + rhs.numerator * denominator);
    denominator *= rhs.denominator;
    normalize();
    return *this;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational tmp = lhs;
    return tmp += rhs;
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return (lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator);
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return (lhs.numerator * rhs.denominator < rhs.numerator * lhs.denominator);
}

Rational& Rational::operator++() {
    numerator += denominator;
    return *this;
}

Rational Rational::operator++(int dummy) {
    Rational original(*this);
    numerator += denominator;
    return original;
}

Rational& operator--(Rational& rhs) {
    rhs += -1;
    return rhs;
}

Rational operator--(Rational& rhs, int dummy) {
    Rational original(rhs);
    rhs += -1;
    return original;
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return (lhs < rhs || lhs == rhs);
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return !(lhs <= rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return !(lhs < rhs);
}

Rational::operator bool() const {
    return (numerator != 0);
}
