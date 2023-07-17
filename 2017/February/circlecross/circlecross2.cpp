#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

int N;

#include <iostream>

enum Color { RED, BLACK };

class Node {
public:
  int key;
  int size; // Size of the subtree rooted at this node
  Color color;
  Node* left;
  Node* right;
  Node* parent;

  Node(int k) : key(k), size(1), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
  Node* root;
  int length; // Length of the Red-Black Tree

  void leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != nullptr)
      y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr)
      root = y;
    else if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;
    y->left = x;
    x->parent = y;
    // Update sizes
    x->size = 1 + getSize(x->left) + getSize(x->right);
    y->size = 1 + getSize(y->left) + getSize(y->right);
  }

  void rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != nullptr)
      y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr)
      root = y;
    else if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;
    y->right = x;
    x->parent = y;
    // Update sizes
    x->size = 1 + getSize(x->left) + getSize(x->right);
    y->size = 1 + getSize(y->left) + getSize(y->right);
  }

  void fixInsert(Node* z) {
    while (z->parent != nullptr && z->parent->color == RED) {
      if (z->parent == z->parent->parent->left) {
        Node* y = z->parent->parent->right;
        if (y != nullptr && y->color == RED) {
          z->parent->color = BLACK;
          y->color = BLACK;
          z->parent->parent->color = RED;
          z = z->parent->parent;
        } else {
          if (z == z->parent->right) {
            z = z->parent;
            leftRotate(z);
          }
          z->parent->color = BLACK;
          z->parent->parent->color = RED;
          rightRotate(z->parent->parent);
        }
      } else {
        Node* y = z->parent->parent->left;
        if (y != nullptr && y->color == RED) {
          z->parent->color = BLACK;
          y->color = BLACK;
          z->parent->parent->color = RED;
          z = z->parent->parent;
        } else {
          if (z == z->parent->left) {
            z = z->parent;
            rightRotate(z);
          }
          z->parent->color = BLACK;
          z->parent->parent->color = RED;
          leftRotate(z->parent->parent);
        }
      }
    }
    root->color = BLACK;
  }

  Node* findNode(Node* current, int key, int& index) {
    if (current == nullptr)
      return nullptr;
    
    if (current->key <= key) {
      // Move to the right subtree since the current node is smaller than or equal to the key
      index += getSize(current->left) + 1;
      return findNode(current->right, key, index);
    } else {
      // Move to the left subtree since the current node is greater than the key
      Node* result = findNode(current->left, key, index);
      if (result == nullptr)
        return current; // Key not found, return the current node (smallest element greater than the key)
      else
        return result; // Key found in the left subtree, propagate the result up
    }
  }

  int getSize(Node* node) {
    return node ? node->size : 0;
  }

public:
  RedBlackTree() : root(nullptr), length(0) {}

  void insert(int key) {
    Node* z = new Node(key);
    Node* y = nullptr;
    Node* x = root;

    while (x != nullptr) {
      y = x;
      y->size++;
      if (z->key < x->key)
        x = x->left;
      else
        x = x->right;
    }

    z->parent = y;
    if (y == nullptr)
      root = z;
    else if (z->key < y->key)
      y->left = z;
    else
      y->right = z;

    fixInsert(z);
    length++;
  }

  int find(int key) {
    int index = 0;
    findNode(root, key, index);
    return index;
  }

  int getLength() {
    return length;
  }
};

int main() {
  freopen("circlecross.in", "r", stdin);
  freopen("circlecross.out", "w", stdout);

  cin >> N;
  vector<int> arr(N*2);
  vector<pii> intervals(N, {-1, -1});
  for (int i = 0; i < 2*N; i++){
    cin >> arr[i];
    arr[i]--;

    if (intervals[arr[i]].first == -1) {
      intervals[arr[i]].first = i;
    } else {
      intervals[arr[i]].second = i;
    }
  }

  // for (int i = 0; i < N; i++) {
  //   cout << intervals[i].first << " " << intervals[i].second << endl;
  // }

  sort(intervals.begin(), intervals.end(), [](auto &left, auto &right) {
    return left.second < right.second;
  });

  RedBlackTree rbt;
  int result = 0;
  for (pii i : intervals) {
    int I = rbt.getLength() - rbt.find(i.first);

    result += (i.second - i.first - 1 - 2*I);

    rbt.insert(i.first);
  }

  cout << result/2 << endl;

  return 0;
}