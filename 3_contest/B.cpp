#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> nodes;

const int cDistanceOfMarathon = 42200;
const int cNumOfSportsmen = 100001;

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
    return Update(nodes, 2 * current_index, left_band, median, searching_pos,
                  val);
  }
  return Update(nodes, 2 * current_index + 1, median, right_band, searching_pos,
                val);
}

int main() {
  int num_of_request;
  std::cin >> num_of_request;
  int num_of_nodes = 1 << (int)std::ceil(std::log2(cDistanceOfMarathon));
  std::vector<int> nodes(2 * num_of_nodes);
  std::vector<int> spotsmens(cNumOfSportsmen, 0);

  for (int i = 0; i < num_of_request; ++i) {
    std::string request;
    std::cin >> request;
    int num_of_sporstmen;
    switch (request[0]) {
      case 'R':
        int point;
        std::cin >> num_of_sporstmen >> point;
        if (spotsmens[num_of_sporstmen] != 0) {
          Update(nodes, 1, 1, num_of_nodes + 1, spotsmens[num_of_sporstmen],
                 -1);
        }
        Update(nodes, 1, 1, num_of_nodes + 1, point, 1);
        spotsmens[num_of_sporstmen] = point;
        break;
      case 'C':
        std::cin >> num_of_sporstmen;
        if (spotsmens[num_of_sporstmen] == 0) {
          std::cout << 0 << "\n";
          break;
        }
        double all = nodes[1];
        if (all == 1) {
          std::cout << 1 << "\n";
          break;
        }
        double lower_than_sportsmen = GetSum(nodes, 1, 1, num_of_nodes + 1, 1,
                                             spotsmens[num_of_sporstmen]);
        all = all - 1;
        std::cout << lower_than_sportsmen / all << "\n";
        break;
    }
  }
}