#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>

int* nodes;

int GetMax(int index, int left_band, int right_band, int request_left,
           int request_right) {
  if ((left_band >= request_left) && (right_band <= request_right)) {
    return nodes[index];
  }
  int answer = 0;
  int median = (left_band + right_band) / 2;
  if (request_left < median) {
    answer = GetMax(2 * index, left_band, median, request_left, request_right);
  }
  if (request_right > median) {
    answer = std::max(answer, GetMax(2 * index + 1, median, right_band,
                                     request_left, request_right));
  }
  return answer;
}

void Update(int current_index, int val) {
  nodes[current_index] = val;
  current_index /= 2;
  while (current_index >= 1) {
    nodes[current_index] =
        std::max(nodes[2 * current_index], nodes[2 * current_index + 1]);
    current_index /= 2;
  }
}

int Find(int st, int num_of_nodes, int value) {
  while (true) {
    if (nodes[st] >= value) {
      if (st >= num_of_nodes) {
        return st;
      }
      st *= 2;
    } else {
      while (st % 2 != 0) {
        st /= 2;
      }
      if (st == 0) {
        return -1;
      }
      st++;
    }
  }
}

int Search(int left_band, int left_bound_for_right, int right_band, int value,
           int num_of_nodes) {
  while (right_band - left_bound_for_right > 1) {
    int median = (left_bound_for_right + right_band) / 2;
    int& rb = num_of_nodes;
    int& lb = left_band;
    int max_on_segment = GetMax(1, 0, rb, lb, median + 1);
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
  nodes = new int[2 * num_of_nodes];

  for (int i = 0; i < 2 * num_of_nodes; i++) {
    nodes[i] = -1;
  }
  for (int i = 0; i < num_of_numbers; i++) {
    int elem;
    std::cin >> elem;
    nodes[num_of_nodes + i] = elem;
    // Update(nodes, i + num_of_nodes, elem);
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
        index--;
        assert(num_of_nodes > 1);
        int pos = Find(index + num_of_nodes, num_of_nodes, value);
        if (pos == -1) {
          std::cout << -1 << "\n";
        } else {
          std::cout << pos - num_of_nodes + 1 << "\n";
        }

        // if (GetMax(1, 0, num_of_nodes, index, num_of_numbers) < value) {
        //   std::cout << -1 << "\n";
        //   break;
        // }
        // if (nodes[index + num_of_nodes] >= value) {
        //   std::cout << index << "\n";
        //   break;
        // }
        // std::cout << BinSearch(index, index - 1, num_of_numbers, value,
        //                        num_of_nodes) +
        //                  1
        //           << "\n";
        break;
      }
      case 0: {
        int pos;
        int elem;
        std::cin >> pos >> elem;
        Update(pos + num_of_nodes - 1, elem);
        break;
      }
    }
  }
  delete[] nodes;
}