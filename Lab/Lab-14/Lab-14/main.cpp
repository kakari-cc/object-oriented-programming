//
//  rec14.cpp
//  Recursion and Exception
//
//  Created by Mingxuan Zhang.
//

#include <iostream>

using namespace std;

bool even_ones(unsigned int num) {
    if(num < 2) {
        return !num;
    }
    return !(num % 2) == even_ones(num / 2);
}

struct Node {
    Node(int data, Node* next = nullptr)
        : data(data)
        , next(next)
    {}
    int data;
    Node* next;
};

Node* value_sum(Node* lst1, Node* lst2) {
    if(lst1 == nullptr & lst2 == nullptr) return nullptr;
    if(lst1 == nullptr) return new Node(lst2->data, value_sum(nullptr, lst2->next));
    if(lst2 == nullptr) return new Node(lst1->data, value_sum(lst1->next, nullptr));
    return new Node(lst1->data + lst2->data, value_sum(lst1->next, lst2->next));
}

struct TNode {
  TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr)
    : data(data), left(left), right(right) {}
  int data;
  TNode *left, *right;
};

int max(TNode* root) {
    if(root == nullptr) throw runtime_error("root");
    try{
        return max(root->data, max(max(root->left), max(root->right)));
    }
    catch (runtime_error& e) {
        return INT_MIN;
    }
}

bool palindrome(char* str, int length) {
    if(length < 2)
        return true;
    if(str[0] == str[length - 1])
        return palindrome(str + 1, length - 2);
    return false;
}

int towers(int num, char start, char spare, char target) {
    if(num == 2) return 3;
    if(num == 1) return 1;
    
    int sum = 0;
    sum += towers(num - 1, start, target, spare);
    sum += towers(1, start, spare, target);
    sum += towers(num - 1, spare, start, target);
    return sum;
}

void mystery(int n) {
   if (n > 1) {
      cout << 'a';
      mystery(n/2);
      cout << 'b';
      mystery(n/2);
   }
   cout << 'c';
    // My Answers
    // 1  | c
    // 2  | a c b c c
    // 3  | a c b c c
    // 4  | a a c b c c b a c b c c c
    // 5  | a a c b c c b a c b c c c
    // 6  | a a c b c c b a c b c c c
    // 7  | a a c b c c b a c b c c c
    // 8  | a a a c b c c b a c b c c c b a a c b c c b a c b c c c c
    // 9  | a a a c b c c b a c b c c c b a a c b c c b a c b c c c c
    // 10 | a a a c b c c b a c b c c c b a a c b c c b a c b c c c c
}

int main() {
    // -- 1 -- //
    cout << boolalpha << even_ones(4666) << endl;
    // -- 2 -- //
    Node* lst1_4 = new Node(4);
    Node* lst1_3 = new Node(3, lst1_4);
    Node* lst1_2 = new Node(2, lst1_3);
    Node* lst1_1 = new Node(1, lst1_2);
    Node* lst2_3 = new Node(5);
    Node* lst2_2 = new Node(5, lst2_3);
    Node* lst2_1 = new Node(5, lst2_2);
    Node* new_node = value_sum(lst1_1, lst2_1);
    for(; new_node; new_node = new_node->next) {
        cout << new_node->data << " ";
    }
    cout << endl;
    // -- 3 -- //
    TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(32, &d, &e);
    cout << max(&f) << endl;
    // -- 4 -- //
    char s[] = "racecar";
    if (palindrome(s, 7)) { cout << "Yes!\n"; }
    // -- 5 -- //
    cout << towers(1, 'a', 'b', 'c') << endl;  // 1
    cout << towers(2, 'a', 'b', 'c') << endl;  // 3
    cout << towers(3, 'a', 'b', 'c') << endl;  // 7
    cout << towers(4, 'a', 'b', 'c') << endl;  // 15
    cout << towers(5, 'a', 'b', 'c') << endl;  // 31
    cout << towers(6, 'a', 'b', 'c') << endl;  // 63
    cout << towers(7, 'a', 'b', 'c') << endl;  // 127
    cout << towers(8, 'a', 'b', 'c') << endl;  // 255
    cout << towers(9, 'a', 'b', 'c') << endl;  // 511
    cout << towers(10, 'a', 'b', 'c') << endl;  // 1023
    // -- 6 -- //
    mystery(10);
    cout << endl;
    return 0;
}
