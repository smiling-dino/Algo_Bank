#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int s;
  std::cin >> s;
  int len_a;
  std::cin >> len_a;
  std::vector<int> a(len_a);
  for (int i = 0; i < len_a; i++) {
    std::cin >> a[i];
  }

  int len_b;
  std::cin >> len_b;
  std::vector<std::pair<int, int>> b(len_b);
  for (int i = 0; i < len_b; i++) {
    std::cin >> b[i].first;
    b[i].second = i;
  }

  int len_c;
  std::cin >> len_c;
  std::vector<std::pair<int, int>> c(len_c);
  for (int i = 0; i < len_c; i++) {
    std::cin >> c[i].first;
    c[i].second = i;
  }
  std::sort(b.begin(), b.end());
  std::sort(c.begin(), c.end());

  std::vector<std::vector<int>> answer;
  for (int i = 0; i < len_a; i++) {
    int l = 0;
    int r = c.size() - 1;
    bool flag = false;
    while ((l < len_b) && (r >= 0)) {
      if (b[l].first + c[r].first == s - a[i]) {
        std::vector<int> ans = {i, b[l].second, c[r].second};
        answer.push_back(ans);
        (r >= 1) ? r-- : l++;
        flag = true;
      } else {
        (b[l].first + c[r].first > s - a[i]) ? r-- : l++;
      }
    }
    if (flag) {
      break;
    }
  }

  std::sort(answer.begin(), answer.end());

  if (answer.empty()) {
    std::cout << -1;
  } else {
    std::cout << answer.front()[0] << " " << answer.front()[1] << " "
              << answer.front()[2] << "\n";
  }
}