#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

int GetMax(std::vector<int>& nodes, int index, int left_band, int right_band,
           int request_left, int request_right) {
  if ((left_band >= request_left) && (right_band <= request_right)) {
    return nodes[index];
  }
  int answer = 0;
  int median = (left_band + right_band) / 2;
  if (request_left < median) {
    answer = GetMax(nodes, 2 * index, left_band, median, request_left,
                    request_right);
  }
  if (request_right > median) {
    answer = std::max(answer, GetMax(nodes, 2 * index + 1, median, right_band,
                                     request_left, request_right));
  }
  return answer;
}

void Update(std::vector<int>& nodes, int current_index, int val) {
  nodes[current_index] = val;
  current_index /= 2;
  while (current_index >= 1) {
    nodes[current_index] =
        std::max(nodes[2 * current_index], nodes[2 * current_index + 1]);
    current_index /= 2;
  }
}

int BinSearch(std::vector<int>& nodes, int left_band, int left_bound_for_right,
              int right_band, int value, int num_of_nodes) {
  while (right_band - left_bound_for_right != 1) {
    int median = (left_bound_for_right + right_band) / 2;
    int max_on_segment =
        GetMax(nodes, 1, 1, num_of_nodes + 1, left_band, median + 1);
    if (max_on_segment >= value) {
      right_band = median;
    } else {
      left_bound_for_right = median;
    }
  }
  return right_band;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);

  int num_of_numbers;
  int num_of_request;
  std::cin >> num_of_numbers >> num_of_request;
  int num_of_nodes = 1 << (int)std::ceil(std::log2(num_of_numbers));
  std::vector<int> nodes(2 * num_of_nodes);
  for (int i = 1; i <= num_of_numbers; i++) {
    int elem;
    std::cin >> elem;
    nodes[num_of_nodes + i - 1] = elem;
    // Update(nodes, i + num_of_nodes - 1, elem);
  }
  for (int i = num_of_nodes - 1; i > 0; i--) {
    nodes[i] = std::max(nodes[2 * i], nodes[2 * i + 1]);
  }

  for (int i = 0; i < num_of_request; ++i) {
    int type_of_request;
    std::cin >> type_of_request;
    switch (type_of_request) {
      case 1: {
        int index;
        int value;
        std::cin >> index >> value;
        if (GetMax(nodes, 1, 1, num_of_nodes + 1, index, num_of_nodes + 1) <
            value) {
          std::cout << -1 << "\n";
          break;
        }
        if (nodes[index + num_of_nodes - 1] >= value) {
          std::cout << index << "\n";
          break;
        }
        std::cout << BinSearch(nodes, index, index, num_of_numbers + 1, value,
                               num_of_nodes)
                  << "\n";
        break;
      }
      case 0: {
        int pos;
        int elem;
        std::cin >> pos >> elem;
        Update(nodes, pos + num_of_nodes - 1, elem);
        break;
      }
    }
  }
}