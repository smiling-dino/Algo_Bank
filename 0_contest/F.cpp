#include <iostream>
#include <vector>

int FindIndexOfArrayPrice(std::vector<int>& row_n, std::vector<int>& row_m,
                          int wide_of_array) {
  int l = 0;
  int r = wide_of_array - 1;
  if (r == 0) {
    return 1;
  }
  while (l < r) {
    int middle = (l + r) / 2;
    if (row_n[middle] == row_m[middle]) {
      return middle + 1;
    }
    if (r - l == 1) {
      int l_value = std::max(row_n[l], row_m[l]);
      int r_value = std::max(row_n[r], row_m[r]);
      return ((r_value < l_value) ? r : l) + 1;
    }
    if (row_n[middle] > row_m[middle]) {
      r = middle;
    } else {
      l = middle;
    }
  }
  return 0;
}
int main() {
  int n;
  int l;
  int m;
  std::cin >> n >> m >> l;
  std::vector<std::vector<int>> matrix_n(n, std::vector<int>(l));
  std::vector<std::vector<int>> matrix_m(m, std::vector<int>(l));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < l; ++j) {
      std::cin >> matrix_n[i][j];
    }
  }

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < l; ++j) {
      std::cin >> matrix_m[i][j];
    }
  }

  int q;
  std::cin >> q;

  for (int i = 1; i <= q; ++i) {
    int a;
    int b;
    std::cin >> a >> b;
    std::cout << FindIndexOfArrayPrice(matrix_n[a - 1], matrix_m[b - 1], l)
              << '\n';
  }
}