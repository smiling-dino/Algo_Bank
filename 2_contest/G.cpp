#include <iostream>
#include <string>
#include <vector>

struct Node {
  Node* l;
  Node* r;
  std::string s;
};

int main() {
  int n;
  std::cin >> n;
  std::vector<Node> nodes(n);
  std::cin >> nodes[0].s;
  for (int i = 1; i < n; i++) {
    std::cin >> nodes[i].s;
    nodes[i].l = &nodes[i - 1];
    nodes[i - 1].r = &nodes[i];
  }
  nodes[n - 1].r = nodes.data();
  nodes[0].l = &nodes[n - 1];
  for (int i = 0; i < n - 3; i++) {
    int index;
    std::cin >> index;
    Node& node = nodes[index - 1];
    std::cout << node.l->s << " " << node.r->s << "\n";
    node.l->r = node.r;
    node.r->l = node.l;
  }
}