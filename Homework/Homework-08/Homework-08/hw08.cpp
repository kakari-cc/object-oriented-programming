//
//  hw08.cpp
//  Polynomial
//
//  Created by Mingxuan Zhang.
//

#include <iostream>
#include <vector>

using namespace std;

string simplify(int coefficient) {  // For Formatting Use
    if(coefficient == 1) return "";
    if(coefficient == -1) return "-";
    return to_string(coefficient);
}

class Polynomial {
private:
    struct Node {  // Doubly Linked
        Node(int coefficient, Node* lower, Node* higher)
            : coefficient(coefficient)
            , lower(lower)
            , higher(higher)
        {}
        int coefficient;
        Node *lower, *higher;
    };
    Node *lowest_term, *highest_term;
    size_t degree;
public:
    Polynomial() : degree(0) {  // Default
        highest_term = lowest_term = new Node(0, nullptr, nullptr);
    }
    
    Polynomial(const vector<int>& init) : degree(init.size() - 1) {  // Vector Parameter
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
    
    Polynomial(const Polynomial& other) {  // Copy
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
    
    Polynomial& operator=(const Polynomial& other) {  // Assignment
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
    
    ~Polynomial() {  // Destructor
        Node* cur = highest_term, *tmp;
        while(cur != nullptr) {
            tmp = cur->lower;
            delete cur;
            cur = tmp;
        }
    }
    
    int evaluate(int x) {
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
    
    Polynomial operator+=(const Polynomial& rhs) {
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
    
    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
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
    
    friend ostream& operator<<(ostream& os, const Polynomial& rhs) {
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
    
};

bool operator!=(const Polynomial& lhs, const Polynomial& rhs) { return !(lhs == rhs); }

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
    Polynomial tmp(lhs);
    tmp += rhs;
    return tmp;
}

void doNothing(Polynomial temp) {}

int main() {
        
    //test constructor
    Polynomial p1({17});                 // 17
    Polynomial p2({1, 2});               // x + 2
    Polynomial p3({-1, 5});              // -x + 5
    Polynomial p4({5, 4, 3, 2, 1});      // 5x^4 + 4x^3 + 3x^2 + 2x + 1
    Polynomial has_a_zero({4, 0, 1, 7}); // 4x^3 + x + 7

    // Polynomial temp(p4);
    // cout << "temp: " << temp << endl;
        
    //    cerr << "displaying polynomials\n";
    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "p3: " << p3 << endl;
    cout << "p4: " << p4 << endl;
    cout << "has_a_zero: " << has_a_zero << endl;

    // Polynomial temp;
    // temp = p2 + p3;
    // cout << "temp: " << temp << endl;
    
    cout << "p2 + p3: " << (p2+p3) << endl;
    cout << "p2 + p4: " << (p2+p4) << endl;
    cout << "p4 + p2: " << (p4+p2) << endl;

    //test copy constructor - the statement below uses the copy constructor
    //to initialize poly3 with the same values as poly4
    Polynomial p5(p4);
    p5 += p3;
    cout << "Polynomial p5(p4);\n"
         << "p5 += p3;\n";

    cout << "p4: " << p4 << endl;
    cout << "p5: " << p5 << endl;


    cout << "Calling doNothing(p5)\n";
    doNothing(p5);
    cout << "p5: " << p5 << endl;

    //tests the assignment operator
    Polynomial p6;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;  // Causes bools true and false to be printed that way.
    cout << "(p4 == p6) is " << (p4 == p6) << endl;
    p6 = p4;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;
    cout << "(p4 == p6) is " << (p4 == p6) << endl;

    //test the evaluaton
    int x = 5;
    cout << "Evaluating p1 at " << x << " yields: " << p1.evaluate(5) << endl;
    cout << "Evaluating p2 at " << x << " yields: " << p2.evaluate(5) << endl;
        
    Polynomial p7({3, 2, 1});           // 3x^2 + 2x + 1
    cout << "p7: " << p7 << endl;
    cout << "Evaluating p7 at " << x << " yields: " << p7.evaluate(5) << endl;

    cout << boolalpha;
    cout << "(p1 == p2) is " << (p1 == p2) << endl;
    cout << "(p1 != p2) is " << (p1 != p2) << endl;

    Polynomial p8({ 1, 1 });
    Polynomial p9({ -1, 1 });
    Polynomial p10({ 0, 0, 2 });
    //p8 + p9 tests if += does the cleanup()
    //p10 tests if constructor does the cleanup()

    cout << "p8: " << p8 << endl
         << "p9: " << p9 << endl
         << "p10: " << p10 << endl;

    cout << "((p8 + p9) == p10) is " << ((p8 + p9) == p10) << endl;
}
