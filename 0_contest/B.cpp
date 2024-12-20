#include <cmath>
#include <iostream>
#include <vector>

const int cPrec = 10;

int main() {
  int n;
  std::cin >> n;
  std::vector<double> elements(n);
  for (int i = 0; i <= n - 1; ++i) {
    double elem;
    std::cin >> elem;
    elements[i] = std::log(elem);
  }
  std::vector<long double> postfix_sum(n);
  postfix_sum.back() = elements.back();
  for (int i = n - 2; i >= 0; --i) {
    postfix_sum[i] = postfix_sum[i + 1] + elements[i];
  }
  int q;
  std::cin >> q;
  for (int j = 1; j <= q; ++j) {
    double l;
    double r;
    std::cin >> l >> r;
    std::cout.precision(cPrec);

    double power_of_exp = 0;
    power_of_exp =
        ((r + 1 == n) ? postfix_sum[l] / (n - l)
                      : (postfix_sum[l] - postfix_sum[r + 1]) / (r - l + 1));
    std::cout << std::fixed << std::exp(power_of_exp) << std::endl;
  }
}