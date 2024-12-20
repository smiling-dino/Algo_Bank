#include <iostream>
#include <string>
#include <vector>

struct Node {
  Node* node_l = nullptr;
  Node* node_r = nullptr;
  int num = 0;
  int left_bound;
  int right_bound;
  Node(int l, int r) : left_bound(l), right_bound(r) {}
  Node(int l, int r, int num) : num(num), left_bound(l), right_bound(r) {}
  void operator=(Node& other) {
    this->node_l = other.node_l;
    this->node_r = other.node_r;
  }
};

int Get(Node* current_node, int index) {
  if (current_node->right_bound - current_node->left_bound == 1) {
    return current_node->num;
  }
  int median = (current_node->right_bound + current_node->left_bound) / 2;
  if (index < median) {
    return Get(current_node->node_l, index);
  }
  return Get(current_node->node_r, index);
}

int Create(Node* current_node, int index, int num,
           std::vector<Node*>& all_nodes) {
  if ((current_node->right_bound - current_node->left_bound == 1) &&
      (current_node->left_bound == index)) {
    current_node->num = num;
    return 0;
  }
  int median = (current_node->right_bound + current_node->left_bound) / 2;
  Node* tmp = nullptr;
  if (index < median) {
    tmp = new Node(current_node->left_bound, median);
    all_nodes.push_back(tmp);
    *tmp = *current_node->node_l;
    current_node->node_l = tmp;
    Create(current_node->node_l, index, num, all_nodes);
    return 0;
  }
  tmp = new Node(median, current_node->right_bound);
  all_nodes.push_back(tmp);
  *tmp = *current_node->node_r;
  current_node->node_r = tmp;
  Create(current_node->node_r, index, num, all_nodes);
  return 0;
}

int Insert(Node* current_node, int index, int num,
           std::vector<Node*>& all_nodes) {
  if ((current_node->right_bound - current_node->left_bound == 1) &&
      (current_node->left_bound == index)) {
    current_node->num = num;
    return 0;
  }
  int median = (current_node->right_bound + current_node->left_bound) / 2;
  if (index < median) {
    if (current_node->node_l == nullptr) {
      current_node->node_l = new Node(current_node->left_bound, median);
      all_nodes.push_back(current_node->node_l);
    }
    Insert(current_node->node_l, index, num, all_nodes);
    return 0;
  }
  if (current_node->node_r == nullptr) {
    current_node->node_r = new Node(median, current_node->right_bound);
    all_nodes.push_back(current_node->node_r);
  }
  Insert(current_node->node_r, index, num, all_nodes);
  return 0;
}

int main() {
  std::vector<Node*> heads;
  std::vector<Node*> all_nodes;
  int n;
  std::cin >> n;
  heads.push_back(new Node(1, n + 1));
  all_nodes.push_back(heads.back());
  for (int i = 0; i < n; i++) {
    int elem;
    std::cin >> elem;
    Insert(heads.back(), i + 1, elem, all_nodes);
  }
  int q;
  std::cin >> q;
  for (int i = 0; i < q; i++) {
    std::string request;
    std::cin >> request;
    int index;
    int version;
    switch (request[0]) {
      case 'c':
        int updated_value;
        std::cin >> version >> index >> updated_value;
        heads.push_back(new Node(1, n + 1));
        all_nodes.push_back(heads.back());
        *heads.back() = *heads[version - 1];
        Create(heads.back(), index, updated_value, all_nodes);
        break;

      case 'g':
        std::cin >> version >> index;
        std::cout << Get(heads[version - 1], index) << "\n";
        break;
    }
  }
  for (size_t i = 0; i < all_nodes.size(); i++) {
    delete all_nodes[i];
  }
}