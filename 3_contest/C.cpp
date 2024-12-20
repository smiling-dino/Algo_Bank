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

int main() {
  int num_of_numbers;
  std::cin >> num_of_numbers;
  int num_of_nodes = 1 << (int)std::ceil(std::log2(num_of_numbers));
  std::vector<int> nodes(2 * num_of_nodes);
  for (int i = 1; i <= num_of_numbers; i++) {
    int elem;
    std::cin >> elem;
    if (i % 2 == 0) {
      Update(nodes, 1, 1, num_of_nodes + 1, i, -elem);

    } else {
      Update(nodes, 1, 1, num_of_nodes + 1, i, elem);
    }
  }
  int num_of_request;
  std::cin >> num_of_request;
  for (int i = 0; i < num_of_request; ++i) {
    int type_of_request;
    std::cin >> type_of_request;
    switch (type_of_request) {
      case 1: {
        int request_left;
        int request_right;
        std::cin >> request_left >> request_right;
        int answer = GetSum(nodes, 1, 1, num_of_nodes + 1, request_left,
                            request_right + 1);
        if (request_left % 2 == 0) {
          std::cout << -answer << "\n";
        } else {
          std::cout << answer << "\n";
        }
        break;
      }
      case 0: {
        int pos;
        int elem;
        std::cin >> pos >> elem;
        if (pos % 2 == 0) {
          Update(nodes, 1, 1, num_of_nodes + 1, pos,
                 -elem - nodes[pos + num_of_nodes - 1]);

        } else {
          Update(nodes, 1, 1, num_of_nodes + 1, pos,
                 elem - nodes[pos + num_of_nodes - 1]);
        }
        break;
      }
    }
  }
}