#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

const int cMagicNumber = 8;

uint32_t cur = 0;
int a = 0;
int b = 0;

uint32_t NextRand24() {
  cur = cur * a + b;
  return cur >> cMagicNumber;
}

uint32_t NextRand32() {
  uint32_t x = NextRand24();
  uint32_t y = NextRand24();
  return (x << cMagicNumber) ^ y;
}

int main() {
  int n;
  std::cin >> n;

  std::cin >> a >> b;

  std::vector<uint32_t> num;

  for (int i = 0; i < n; i++) {
    num.push_back(NextRand32());
  }
  std::nth_element(num.begin(), num.begin() + (num.size() + 1) / 2, num.end());
  long long median = num[(num.size() + 1) / 2];

  uint64_t sum = 0;
  for (uint32_t elem : num) {
    sum += std::abs(elem - median);
  }
  std::cout << sum << "\n";
}