#include <iostream>

using namespace std;

struct TNode {
  TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr)
    : data(data), left(left), right(right) {}
  int data;
  TNode *left, *right;
};

int max(TNode* root) {
    if(root == nullptr) return INT_MIN;
    return max(root->data, max(max(root->left), max(root->right)));
}

int main() {

  TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(32, &d, &e);
  cout << max(&f) << endl;

}

  
  
