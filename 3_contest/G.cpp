#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

long long GetSum(std::vector<long long>& nodes, int index, int left_band,
                 int right_band, int request_left, int request_right) {
  if ((left_band >= request_left) && (right_band <= request_right)) {
    return nodes[index];
  }
  long long answer = 0;
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

void Update(std::vector<long long>& nodes, int current_index, int left_band,
            int right_band, int searching_pos, int val) {
  nodes[current_index] += val;
  if (left_band == right_band - 1) {
    return;
  }
  int median = (left_band + right_band) / 2;
  if (searching_pos < median) {
    return Update(nodes, 2 * current_index, left_band, median, searching_pos,
                  val);
  }
  return Update(nodes, 2 * current_index + 1, median, right_band, searching_pos,
                val);
}

int BinSearch(std::vector<int>& numbers, int search_val) {
  int l = -1;
  int r = numbers.size() - 1;

  while (r - l > 1) {
    int m = (l + r) / 2;
    int val_of_m = numbers[m];
    if (val_of_m >= search_val) {
      r = m;
    } else {
      l = m;
    }
  }
  // if (r == numbers.size() || numbers[r] != search_val)return -1;
  return r + 1;
}

void Print(std::vector<int>& nodes) {
  for (auto node : nodes) {
    std::cout << node << " ";
  }
  std::cout << "\n";
}

int main() {
  int num_of_request;
  std::cin >> num_of_request;
  std::vector<std::pair<char, int>> requests(num_of_request);
  std::vector<int> numbers(num_of_request);
  for (int i = 0; i < num_of_request; ++i) {
    std::cin >> requests[i].first >> requests[i].second;
    numbers[i] = requests[i].second;
  }
  std::sort(numbers.begin(), numbers.end());
  auto last = std::unique(numbers.begin(), numbers.end());
  numbers.erase(last, numbers.end());

  int num_of_nodes = 1 << (int)std::ceil(std::log2(numbers.size()));
  std::vector<long long> nodes(2 * num_of_nodes);

  for (auto request : requests) {
    switch (request.first) {
      case '+':
        // std::cout << request.second << " "
        //           << BinSearch(numbers, request.second) << "\n";
        Update(nodes, 1, 1, num_of_nodes + 1,
               BinSearch(numbers, request.second), request.second);
        // Print(nodes);
        break;
      case '?':

        std::cout << GetSum(nodes, 1, 1, num_of_nodes + 1, 1,
                            BinSearch(numbers, request.second) + 1)
                  << "\n";
        break;
    }
  }
}