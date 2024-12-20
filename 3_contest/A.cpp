#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

struct Node {
  std::pair<int, int> first_statistik = {0, 0};
  std::pair<int, int> second_statistik = {2000000, 0};
};

Node Merge(Node& node_1, Node& node_2) {
  std::vector<std::pair<int, int>> statics;
  statics.push_back(node_1.first_statistik);
  statics.push_back(node_1.second_statistik);
  statics.push_back(node_2.first_statistik);
  statics.push_back(node_2.second_statistik);
  std::sort(statics.begin(), statics.end());
  std::unique(statics.begin(), statics.end());
  return Node({statics[0], statics[1]});
}

int main() {
  int num_of_numbers;
  int num_of_requests;
  std::cin >> num_of_numbers >> num_of_requests;
  std::vector<int> numbers(num_of_numbers);
  std::vector<std::vector<Node>> sparse(std::__lg(num_of_numbers) + 1,
                                        std::vector<Node>(num_of_numbers));
  for (int i = 0; i < num_of_numbers; ++i) {
    std::cin >> numbers[i];
    sparse[0][i].first_statistik.first = numbers[i];
    sparse[0][i].first_statistik.second = i;
  }
  for (int pow_of_segment = 1; pow_of_segment <= std::__lg(num_of_numbers);
       pow_of_segment++) {
    int size_of_segment = pow(2, pow_of_segment);
    for (int pos_of_segment = 0;
         pos_of_segment <= num_of_numbers - size_of_segment; pos_of_segment++) {
      sparse[pow_of_segment][pos_of_segment] = Merge(
          sparse[pow_of_segment - 1][pos_of_segment],
          sparse[pow_of_segment - 1][pos_of_segment + size_of_segment / 2]);
    }
  }

  for (int i = 0; i < num_of_requests; ++i) {
    int left;
    int right;
    std::cin >> left >> right;
    left--;
    int size_of_segment =
        std::pow(2, static_cast<int>(std::ceil(std::log2(right - left)))) / 2;
    int pow_of_segment = std::__lg(size_of_segment);
    Node left_segment = sparse[pow_of_segment][left];
    Node right_segment = sparse[pow_of_segment][right - size_of_segment];
    std::cout << Merge(left_segment, right_segment).second_statistik.first
              << "\n";
  }
}