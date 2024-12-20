#include <iostream>
#include <string>

struct Node {
  int key;
  int height;
  Node* left;
  Node* right;
  Node(int value) : key(value), height(1), left(nullptr), right(nullptr) {}
};

int Height(Node* node) { return (node != nullptr ? node->height : 0); }

Node* Right(Node* b) {
  Node* a;
  a = b->left;
  Node* c;
  c = a->right;
  a->right = b;
  b->left = c;
  b->height = (Height(b->left) > Height(b->right) ? Height(b->left)
                                                  : Height(b->right)) +
              1;
  a->height = (Height(a->left) > Height(a->right) ? Height(a->left)
                                                  : Height(a->right)) +
              1;
  return a;
}

Node* Left(Node* a) {
  Node* b;
  b = a->right;
  Node* c;
  c = b->left;
  b->left = a;
  a->right = c;
  a->height = (Height(a->left) > Height(a->right) ? Height(a->left)
                                                  : Height(a->right)) +
              1;
  b->height = (Height(b->left) > Height(b->right) ? Height(b->left)
                                                  : Height(b->right)) +
              1;
  return b;
}

Node* Insert(Node* node, int key) {
  if (node == nullptr) {
    return new Node(key);
  }

  if (key < node->key) {
    node->left = Insert(node->left, key);

  } else if (key > node->key) {
    node->right = Insert(node->right, key);

  } else {
    return node;
  }

  node->height =
      (Height(node->left) > Height(node->right) ? Height(node->left)
                                                : Height(node->right)) +
      1;
  int balance;
  balance = (node != nullptr ? (Height(node->left) - Height(node->right)) : 0);

  if (balance > 1) {
    if (key > (node->left)->key) {
      node->left = Left(node->left);
    }

    return Right(node);
  }

  if (balance < -1) {
    if (key < node->right->key) {
      node->right = Right(node->right);
    }

    return Left(node);
  }

  return node;
}

Node* LowerBound(Node* node, int x) {
  if (node == nullptr) {
    return nullptr;
  }

  if (node->key == x) {
    return node;
  }

  if (node->left != nullptr && node->key > x) {
    Node* mininode;
    mininode = LowerBound(node->left, x);

    if (mininode != nullptr) {
      return mininode;
    }

    return node;
  }

  if (node->key > x) {
    return node;
  }

  if (node->right != nullptr && node->key < x) {
    Node* mininode;
    mininode = LowerBound(node->right, x);

    if (mininode != nullptr) {
      return mininode;
    }

    return nullptr;
  }

  return nullptr;
}

void Delete(Node* root) {
  if (root != nullptr) {
    Delete(root->left);
    Delete(root->right);
    delete root;
  }
}

int main() {
  int input_q;
  std::cin >> input_q;
  int input_x;
  int answer_y;
  std::string string_new;
  std::string string_old;
  string_old = "";
  Node* root;
  root = nullptr;

  for (int i = 0; i < input_q; ++i) {
    std::cin >> string_new;
    std::cin >> input_x;

    if (string_new == "?") {
      Node* node;
      node = LowerBound(root, input_x);
      std::cout << (node != nullptr ? node->key : -1) << '\n';
      string_old = "?";
      answer_y = (node != nullptr ? node->key : -1);

    } else if (string_old.empty() || string_old == "+") {
      root = Insert(root, input_x);
      string_old = "+";

    } else {
      root = Insert(root, (input_x + answer_y) % (4 * 4 * 4 * 4 * 2 * 5 * 5 *
                                                  5 * 5 * 5 * 5 * 5 * 5 * 5));
      string_old = "+";
    }
  }

  Delete(root);
}