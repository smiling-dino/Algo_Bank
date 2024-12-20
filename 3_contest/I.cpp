#include <math.h>

#include <algorithm>
#include <iostream>
#include <vector>

struct Node {
  std::vector<int> numbers;
};

struct Request {
  int request_left;
  int request_right;
  int left_bound_of_numbers;
  int right_bound_of_numbers;

  Request(int request_left, int request_right, int x, int y)
      : request_left(request_left), request_right(request_right), left_bound_of_numbers(x), right_bound_of_numbers(y){};
};

void Merge(std::vector<int>& vec_1, std::vector<int>& vec_2,
           std::vector<int>& answer) {
  answer.clear();
  answer.reserve(vec_1.size() + vec_2.size());
  size_t left = 0;
  size_t right = 0;
  while ((left < vec_1.size()) || (right < vec_2.size())) {
    if (left == vec_1.size()) {
      answer.push_back(vec_2[right]);
      right++;
      continue;
    }
    if (right == vec_2.size()) {
      answer.push_back(vec_1[left]);
      left++;
      continue;
    }
    if (vec_1[left] < vec_2[right]) {
      answer.push_back(vec_1[left]);
      left++;
    } else {
      answer.push_back(vec_2[right]);
      right++;
    }
  }
}

int Create(std::vector<Node>& nodes, int current_index, int left_bound,
           int right_bound) {
  if (right_bound - left_bound == 1) {
    return 0;
  }
  int median = (left_bound + right_bound) / 2;
  Create(nodes, 2 * current_index, left_bound, median);
  Create(nodes, 2 * current_index + 1, median, right_bound);

  Merge(nodes[2 * current_index].numbers, nodes[2 * current_index + 1].numbers,
        nodes[current_index].numbers);
  return 0;
}

long long Get(std::vector<Node>& nodes, int current_index, int left_bound,
              int right_bound, Request& request) {
  if ((left_bound >= request.request_right) || (right_bound <= request.request_left)) {
    return 0;
  }
  if ((request.request_left <= left_bound) && (right_bound <= request.request_right)) {
    auto lower = std::lower_bound(nodes[current_index].numbers.begin(),
                                  nodes[current_index].numbers.end(), request.left_bound_of_numbers);
    auto upper = std::upper_bound(nodes[current_index].numbers.begin(),
                                  nodes[current_index].numbers.end(), request.right_bound_of_numbers);
    return upper - lower;
  }
  int median = (left_bound + right_bound) / 2;

  return Get(nodes, 2 * current_index, left_bound, median, request) +
         Get(nodes, 2 * current_index + 1, median, right_bound, request);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int num_numbers;
  int num_requests;
  std::cin >> num_numbers >> num_requests;
  int num_of_nodes = 1 << (int)std::ceil(std::log2(num_numbers));
  std::vector<Node> nodes(2 * num_of_nodes);
  for (int i = 0; i < num_numbers; i++) {
    int elem;
    std::cin >> elem;
    nodes[num_of_nodes + i].numbers.push_back(elem);
  }
  Create(nodes, 1, 1, num_of_nodes + 1);
  for (int i = 0; i < num_requests; i++) {
    int request_left;
    int request_right;
    int left_bound_of_numbers;
    int right_bound_of_numbers;
    std::cin >> request_left >> request_right >> left_bound_of_numbers >> right_bound_of_numbers;
    Request request(request_left, request_right + 1, left_bound_of_numbers, right_bound_of_numbers);
    std::cout << Get(nodes, 1, 1, num_of_nodes + 1, request) << "\n";
  }
}