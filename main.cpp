#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// A node struct with a nodes info
struct Node {
  int key;
  Node* left;
  Node* right;
  int height;
  Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

// find height of node n
static inline int h(Node* n) { return n ? n->height : 0; }
// find balance for avl of node n
static inline int balance(Node* n) { return n ? h(n->left) - h(n->right) : 0; }

// rotate right
Node* rotateRight(Node* y) {
  Node* x = y->left;
  Node* T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(h(y->left), h(y->right)) + 1;
  x->height = max(h(x->left), h(x->right)) + 1;
  return x;
}

// rotate left
Node* rotateLeft(Node* x) {
  Node* y = x->right;
  Node* T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(h(x->left), h(x->right)) + 1;
  y->height = max(h(y->left), h(y->right)) + 1;
  return y;
}

Node* insert(Node* root, int key) {
  // create new node, base case
  if (!root) {
    return new Node(key);
  }
  // binary search going down the tree
  if (key < root->key) {
    root->left = insert(root->left, key);
  } else if (key > root->key) {
    root->right = insert(root->right, key);
  } else {
    return root;  // ignore duplicates
  }
  root->height = 1 + max(h(root->left), h(root->right));
  int b = balance(root);

  // if balance left heavy
  if (b > 1 && key < root->left->key) {
    return rotateRight(root);
  }
  // if balance right heavy
  if (b < -1 && key > root->right->key) {
    return rotateLeft(root);
  }
  // left rotate on left child, then right rotate on root
  if (b > 1 && key > root->left->key) {
    root->left = rotateLeft(root->left);
    return rotateRight(root);
  }
  // right rotate on right child, then left rotate on root
  if (b < -1 && key < root->right->key) {
    root->right = rotateRight(root->right);
    return rotateLeft(root);
  }
  return root;
}

Node* maxValueNode(Node* node) {
  Node* curr = node;
  while (curr && curr->right) {
    // traverse to right most node for swapping
    curr = curr->right;
  }
  return curr;
}

Node* deleteNode(Node* root, int key) {
  if (!root) {
    return root;
  }

  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);
  else {
    // node to delete found
    if (!root->left || !root->right) {
      Node* child = root->left ? root->left : root->right;
      // 0 children
      if (!child) {
        delete root;
        return nullptr;
      } else {
        // 1 child
        *root = *child;  // copy child into root
        delete child;
      }
    } else {
      // two children
      Node* maxValue = maxValueNode(root->left);  // find largest on left
      root->key = maxValue->key;
      root->left = deleteNode(
          root->left, maxValue->key);  // replace and delete max value node
    }
  }

  // rebalance on the way up
  root->height = 1 + max(h(root->left), h(root->right));
  int b = balance(root);

  // left heavy
  if (b > 1 && balance(root->left) >= 0) {
    return rotateRight(root);
  }

  // right heavy
  if (b < -1 && balance(root->right) <= 0) {
    return rotateLeft(root);
  }

  // left-right rotate
  if (b > 1 && balance(root->left) < 0) {
    root->left = rotateLeft(root->left);
    return rotateRight(root);
  }

  // right-left rotate
  if (b < -1 && balance(root->right) > 0) {
    root->right = rotateRight(root->right);
    return rotateLeft(root);
  }
  return root;
}

void preorder(Node* n, vector<int>& out) {
  if (!n) return;
  out.push_back(n->key);    // curr
  preorder(n->left, out);   // left
  preorder(n->right, out);  // right
}
void inorder(Node* n, vector<int>& out) {
  if (!n) return;
  inorder(n->left, out);   // left
  out.push_back(n->key);   // curr
  inorder(n->right, out);  // right
}
void postorder(Node* n, vector<int>& out) {
  if (!n) return;
  postorder(n->left, out);   // left
  postorder(n->right, out);  // right
  out.push_back(n->key);     // curr
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // initialise tree
  Node* root = nullptr;
  vector<string> tok;  // tokenise input
  string s;
  while (cin >> s) {
    tok.push_back(s);
  }
  if (tok.empty()) return 0;

  // loop through token except last token
  //  A for insert and use substr to get the key
  //  D for delete
  for (size_t i = 0; i + 1 < tok.size(); i++) {
    const string& t = tok[i];
    if (t[0] == 'A') {
      int v = stoi(t.substr(1));  // converts the type
      root = insert(root, v);
    } else if (t[0] == 'D') {
      int v = stoi(t.substr(1));
      root = deleteNode(root, v);
    }
  }

  // now for the pre/in/post or empty outputs
  string finish = tok.back();
  vector<int> output;
  if (finish == "PRE") {
    preorder(root, output);
  } else if (finish == "IN") {
    inorder(root, output);
  } else if (finish == "POST") {
    postorder(root, output);
  }
  if (output.empty()) {
    cout << "EMPTY";
  } else {
    // output the traversal
    for (size_t i = 0; i < output.size(); i++) {
      if (i) cout << ' ';
      cout << output[i];
    }
  }
  return 0;
}
