// CtrlC CtrlV production from https://neerc.ifmo.ru/wiki

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

long long GetSum(std::vector<std::vector<long long>>& fenvic, int x, int y) {
  long long result = 0;
  for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
    for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
      result += fenvic[i][j];
    }
  }
  return result;
}

void Update(std::vector<std::vector<long long>>& fenvic, int n, int x, int y,
            int delta) {
  for (int i = x; i < n + 1; i = (i | (i + 1))) {
    for (int j = y; j < n + 1; j = (j | (j + 1))) {
      fenvic[i][j] += delta;
    }
  }
}

int main() {
  int n;
  int num_of_request;
  std::cin >> n >> num_of_request;
  std::vector<std::vector<long long>> fenvic(n + 1,
                                             std::vector<long long>(n + 1, 0));
  for (int i = 0; i < num_of_request; i++) {
    std::string request;
    std::cin >> request;
    int x_1 = 0;
    int y_1 = 0;
    int x_2 = 0;
    int y_2 = 0;
    switch (request[0]) {
      case 'A':
        std::cin >> x_1 >> y_1;
        Update(fenvic, n, x_1, y_1, 1);
        break;
      case 'G':
        std::cin >> x_1 >> y_1 >> x_2 >> y_2;
        int tmp_x = (x_1 >= x_2) ? x_1 : x_2;
        int tmp_y = (y_1 >= y_2) ? y_1 : y_2;
        x_1 = std::min(x_1, x_2);
        y_1 = std::min(y_1, y_2);
        x_2 = tmp_x;
        y_2 = tmp_y;
        long long sum =
            GetSum(fenvic, x_2, y_2) + GetSum(fenvic, x_1 - 1, y_1 - 1) -
            GetSum(fenvic, x_1 - 1, y_2) - GetSum(fenvic, x_2, y_1 - 1);
        std::cout << sum << "\n";
        break;
    }
  }
}
