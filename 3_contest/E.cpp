#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

int GetSum(std::vector<int>& nodes, int index, int left_band, int right_band,
           int request_left, int request_right) {
  if ((left_band >= request_left) && (right_band <= request_right)) {
    return nodes[index];
  }
  int answer = 0;
  int median = (left_band + right_band) / 2;
  if (request_left < median) {
    answer += GetSum(nodes, 2 * index, left_band, median, request_left,
                     request_right);
  }
  if (request_right > median) {
    answer += GetSum(nodes, 2 * index + 1, median, right_band, request_left,
                     request_right);
  }
  return answer;
}

void Update(std::vector<int>& nodes, int current_index, int left_band,
            int right_band, int searching_pos, int val) {
  nodes[current_index] += val;
  if (left_band == right_band - 1) {
    return;
  }
  int median = (left_band + right_band) / 2;
  if (searching_pos < median) {
    Update(nodes, 2 * current_index, left_band, median, searching_pos, val);
  } else {
    Update(nodes, 2 * current_index + 1, median, right_band, searching_pos,
           val);
  }
}

int IndexFromSum(std::vector<int>& nodes, int current_index, int sum,
                 int num_of_nodes) {
  if ((sum == nodes[current_index]) && (current_index >= num_of_nodes)) {
    return current_index - num_of_nodes + 1;
  }
  if (nodes[2 * current_index] >= sum) {
    return IndexFromSum(nodes, 2 * current_index, sum, num_of_nodes);
  }
  return IndexFromSum(nodes, 2 * current_index + 1,
                      sum - nodes[2 * current_index], num_of_nodes);
}

int main() {
  std::vector<int> numbers;
  while (std::cin) {
    int elem;
    std::cin >> elem;
    numbers.push_back(elem);
  }
  numbers.pop_back();
  int num_of_numbers = numbers.size();
  int num_of_nodes = 1 << (int)std::ceil(std::log2(num_of_numbers));
  std::vector<int> initial_massive;
  std::vector<int> nodes(2 * num_of_nodes, 0);
  for (size_t i = 0; i < numbers.size(); i++) {
    Update(nodes, 1, 1, num_of_nodes + 1, i + 1, 1);
  }

  std::vector<int> original_numbers(num_of_numbers);
  for (int i = 0; i < num_of_numbers; i++) {
    int index_of_i_num = IndexFromSum(nodes, 1, numbers[i] + 1, num_of_nodes);
    original_numbers[index_of_i_num - 1] = i + 1;
    Update(nodes, 1, 1, num_of_nodes + 1, index_of_i_num, -1);
  }
  std::vector<int> reverse_numbers(num_of_numbers);
  std::vector<int> indexes_of_elem(num_of_numbers);
  for (size_t i = 0; i < original_numbers.size(); i++) {
    reverse_numbers[original_numbers[i] - 1] = i + 1;
    indexes_of_elem[i] = original_numbers[i];
  }
  std::fill(nodes.begin(), nodes.end(), 0);
  for (size_t i = 0; i < numbers.size(); i++) {
    Update(nodes, 1, 1, num_of_nodes + 1, i + 1, 1);
  }
  std::vector<int> permutations(num_of_numbers);
  for (int i = 0; i < num_of_numbers; i++) {
    permutations[i] =
        GetSum(nodes, 1, 1, num_of_nodes + 1, 1, indexes_of_elem[i]);
    Update(nodes, 1, 1, num_of_nodes + 1, indexes_of_elem[i], -1);
  }
  for (size_t i = 0; i < permutations.size(); i++) {
    std::cout << permutations[i] << " ";
  }
}