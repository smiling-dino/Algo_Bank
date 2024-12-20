#include <iostream>
#include <vector>

struct Node {
  Node* ptr_to_parent = nullptr;
  Node* ptr_to_left_son = nullptr;
  Node* ptr_to_right_son = nullptr;
  int key = 0;
  int prior = 0;

  Node(){};
  Node(int key, int prior) : key(key), prior(prior){};

  void PrintNode() const {
    if (ptr_to_parent != nullptr) {
      std::cout << ptr_to_parent->key + 1;
    } else {
      std::cout << 0;
    }
    std::cout << " ";
    if (ptr_to_left_son != nullptr) {
      std::cout << ptr_to_left_son->key + 1;
    } else {
      std::cout << 0;
    }
    std::cout << " ";
    if (ptr_to_right_son != nullptr) {
      std::cout << ptr_to_right_son->key + 1;
    } else {
      std::cout << 0;
    }
    std::cout << "\n";
  }
};

int main() {
  int num_of_nodes;
  std::cin >> num_of_nodes;
  static std::vector<Node> nodes;
  nodes.reserve(num_of_nodes);
  std::vector<Node*> stack;
  for (int i = 0; i < num_of_nodes; i++) {
    int key;
    int prior;
    std::cin >> key >> prior;
    nodes.push_back(Node(i, prior));
    Node* ptr_last_del = nullptr;
    while ((!stack.empty()) && (stack.back()->prior > prior)) {
      ptr_last_del = stack.back();
      stack.pop_back();
    }
    if (!stack.empty()) {
      stack.back()->ptr_to_right_son = &nodes.back();
      nodes.back().ptr_to_parent = stack.back();
    }
    if (ptr_last_del != nullptr) {
      nodes.back().ptr_to_left_son = ptr_last_del;
      ptr_last_del->ptr_to_parent = &nodes.back();
    }
    stack.push_back(&nodes.back());
  }
  std::cout << "YES\n";
  for (size_t i = 0; i < nodes.size(); i++) {
    nodes[i].PrintNode();
  }
}