#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <vector>

std::string simplify(int coefficient);  // For Formatting Use

class Polynomial {
    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& rhs);
private:
    struct Node {  // Doubly Linked
        Node(int coefficient, Node* lower, Node* higher);
        int coefficient;
        Node *lower, *higher;
    };
    Node *lowest_term, *highest_term;
    size_t degree;
public:
    Polynomial();  // Default
    Polynomial(const std::vector<int>& init);  // Vector Parameter
    Polynomial(const Polynomial& other);  // Copy
    Polynomial& operator=(const Polynomial& other);  // Assignment
    ~Polynomial();  // Destructor
    int evaluate(int x);
    Polynomial operator+=(const Polynomial& rhs);
};

bool operator!=(const Polynomial& lhs, const Polynomial& rhs);
Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);

#endif
