#include <iostream>
#include <vector>

using std::cout, std::cin, std::vector;

bool BinFinder(const vector<int>& v, int num) {
  int l = 0;
  int r = v.size() - 1;
  while (l <= r) {
    int elem = v[(l + r) / 2];
    if (elem == num) {
      return true;
    }
    if (elem > num) {
      r = (l + r) / 2 - 1;
    } else {
      l = (l + r) / 2 + 1;
    }
  }
  return false;
}
int main() {
  int n;
  int k;
  cin >> n >> k;
  vector<int> vec(n);
  for (std::size_t i = 0; i < vec.size(); ++i) {
    cin >> vec[i];
  }
  for (int i = 1; i <= k; ++i) {
    int elem;
    cin >> elem;
    cout << (BinFinder(vec, elem) ? "YES" : "NO") << std::endl;
  }
}