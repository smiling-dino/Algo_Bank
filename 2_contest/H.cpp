#include <cmath>
#include <iostream>
#include <string>
#include <vector>

int main() {
  int n;
  std::cin >> n;

  std::vector<std::vector<long long>> table(n);
  for (int i = 0; i < n; i++) {
    table[i].resize(3);
    std::cin >> table[i][2];
  }

  std::vector<int> stack_of_min_from_l;
  stack_of_min_from_l.push_back(-1);
  for (int i = 0; i < n; i++) {
    while ((stack_of_min_from_l.back() != -1) &&
           (table[i][2] <= table[stack_of_min_from_l.back()][2])) {
      stack_of_min_from_l.pop_back();
    }
    table[i][0] = stack_of_min_from_l.back();
    stack_of_min_from_l.push_back(i);
  }

  std::vector<int> stack_of_min_from_r;
  stack_of_min_from_r.push_back(n);
  for (int i = n - 1; i >= 0; i--) {
    while ((stack_of_min_from_r.back() != n) &&
           (table[i][2] <= table[stack_of_min_from_r.back()][2])) {
      stack_of_min_from_r.pop_back();
    }
    table[i][1] = stack_of_min_from_r.back();
    stack_of_min_from_r.push_back(i);
  }

  long long max_squere = 0;
  for (int i = 0; i < n; i++) {
    max_squere =
        std::max(max_squere, table[i][2] * (table[i][1] - table[i][0] - 1));
  }

  std::cout << max_squere;
}