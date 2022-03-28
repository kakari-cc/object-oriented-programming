//
//  rec-08.cpp
//  Operator Overloading
//
//  Created by Mingxuan Zhang.
//

#include <iostream>

using namespace std;

int greatestCommonDivisor(int x, int y) {
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

class Rational {
    int numerator, denominator;
    void normalize();
    
public:
    Rational(int numerator = 0, int denominator = 1);
    friend ostream& operator<<(ostream& os, const Rational& rhs);
    friend istream& operator>>(istream& is, Rational& rhs);
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

int main() {
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;    // Implement as member
    cout << "a = " << a << endl;
    
    // Implement + as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;
    
    // How does this manage to work?
    // It does NOT require writing another == operator.
    cout << "1 == one: " << boolalpha << (1 == one) << endl;
    
    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing?
    //  cout << "a-- -- = " << (a-- --) << endl;
    cout << "a = " << a << endl;


    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    }

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    }

    cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalves(3, 2);
    Rational minusFive(-5);
    cout << twoFifths << " < " << threeHalves << " : "
         << (twoFifths < threeHalves) << endl;
    cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
    cout << threeHalves << " < " << twoFifths << " : "
         << (threeHalves < twoFifths) << endl;
    cout << threeHalves << " > " << threeHalves << " : "
         << (threeHalves > threeHalves) << endl;
    cout << threeHalves << " >= " << threeHalves << " : "
         << (threeHalves >= threeHalves) << endl;
    cout << minusFive << " >= " << threeHalves << " : "
         << (minusFive >= threeHalves) << endl;
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
