#include <iostream>
#include <vector>

#include "polynomial.h"

using namespace std;

string simplify(int coefficient) {  // For Formatting Use
    if(coefficient == 1) return "";
    if(coefficient == -1) return "-";
    return to_string(coefficient);
}

Polynomial::Node::Node(int coefficient, Polynomial::Node* lower, Polynomial::Node* higher)
        : coefficient(coefficient)
        , lower(lower)
        , higher(higher)
    {}

Polynomial::Polynomial() : degree(0) {  // Default
        highest_term = lowest_term = new Node(0, nullptr, nullptr);
    }
    
Polynomial::Polynomial(const vector<int>& init) : degree(init.size() - 1) {  // Vector Parameter
    highest_term = new Node(0, nullptr, nullptr);
    if(init.size() > 0) highest_term->coefficient = init[0];
    Node *new_node = highest_term, *tmp;
    for(size_t i = 1; i < init.size(); i++) {
        tmp = new_node;
        new_node = new Node(init[i], nullptr, new_node);
        tmp->lower = new_node;
    }
    lowest_term = new_node;
    while(highest_term->coefficient == 0 && highest_term != lowest_term) {  // Cleanup Leading 0s
        Node* tmp = highest_term;
        highest_term = highest_term->lower;
        delete tmp;
        highest_term->higher = nullptr;
        degree--;
    }
}
    
Polynomial::Polynomial(const Polynomial& other) {  // Copy
    degree = other.degree;
    Node* tmp = highest_term = new Node(other.highest_term->coefficient, nullptr, nullptr);
    Node* cur = other.highest_term->lower;
    while(cur != nullptr) {
        tmp->lower = new Node(cur->coefficient, nullptr, tmp);
        tmp = tmp->lower;
        cur = cur->lower;
    }
    lowest_term = tmp;
}
    
Polynomial& Polynomial::operator=(const Polynomial& other) {  // Assignment
    degree = other.degree;
    Node* tmp = highest_term = new Node(other.highest_term->coefficient, nullptr, nullptr);
    Node* cur = other.highest_term->lower;
    while(cur != nullptr) {
        tmp->lower = new Node(cur->coefficient, nullptr, tmp);
        tmp = tmp->lower;
        cur = cur->lower;
    }
    lowest_term = tmp;
    return *this;
}
    
Polynomial::~Polynomial() {  // Destructor
    Node* cur = highest_term, *tmp;
    while(cur != nullptr) {
        tmp = cur->lower;
        delete cur;
        cur = tmp;
    }
}
    
int Polynomial::evaluate(int x) {
    int sum = 0;
    Node* cur = highest_term;
    size_t cur_degree = degree;
    while(cur != nullptr) {
        sum += cur->coefficient * pow(x, cur_degree);
        cur = cur->lower;
        cur_degree--;
    }
    return sum;
}
    
Polynomial Polynomial::operator+=(const Polynomial& rhs) {
    Node *cur = lowest_term, *r_cur = rhs.lowest_term;
    int carry = 0;
    while(r_cur != nullptr) {
        cur->coefficient += (r_cur->coefficient + carry);
        carry = cur->coefficient / 10;
        cur->coefficient %= 10;
        if(cur->higher == nullptr) {
            cur->higher = new Node(0, cur, nullptr);
            highest_term = cur->higher;
            degree++;
        }
        cur = cur->higher;
        r_cur = r_cur->higher;
    }
    if(carry) cur->coefficient = carry;
    while(highest_term->coefficient == 0 && highest_term != lowest_term) {  // Cleanup Leading 0s
        Node* tmp = highest_term;
        highest_term = highest_term->lower;
        delete tmp;
        highest_term->higher = nullptr;
        degree--;
    }
    return *this;
}
    
bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
    if (lhs.degree != rhs.degree) return false;
    Polynomial::Node* l_cur = lhs.highest_term;
    Polynomial::Node* r_cur = rhs.highest_term;
    while(l_cur != nullptr && r_cur != nullptr) {
        if(l_cur->coefficient != r_cur->coefficient) return false;
        l_cur = l_cur->lower;
        r_cur = r_cur->lower;
    }
    return true;
}
    
ostream& operator<<(ostream& os, const Polynomial& rhs) {
//        /* -- Debug Use Only -- */
//        Polynomial::Node* cur = rhs.lowest_term;
//        int deg = 0;
//        while(cur != nullptr) {
//            cout << cur->coefficient << "x^" << deg << " + ";
//            cur = cur->higher;
//            deg++;
//        }
//        os << "deg:" << rhs.degree;
    Polynomial::Node* cur = rhs.highest_term;
    size_t cur_degree = rhs.degree;
    while(cur != nullptr) {
        if(cur->coefficient != 0) {
            if(cur_degree == 0) {
                if(cur_degree != rhs.degree)
                    os << " + ";
                os << cur->coefficient;
            }
            else if(cur_degree == 1) {  // Implicit Coefficient
                if(cur_degree != rhs.degree)
                    os << " + ";
                os << simplify(cur->coefficient) << "x";
            }
            else {
                if(cur_degree != rhs.degree)
                    os << " + ";
                os << simplify(cur->coefficient) << "x^" << cur_degree;
            }
        }
        else if(rhs.degree == 0)  // Only "0"
            os << "0";
        cur = cur->lower;
        cur_degree--;
    }
    return os;
}

bool operator!=(const Polynomial& lhs, const Polynomial& rhs) { return !(lhs == rhs); }

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
    Polynomial tmp(lhs);
    tmp += rhs;
    return tmp;
}
