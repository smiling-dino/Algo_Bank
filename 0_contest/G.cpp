#include <iostream>
#include <vector>

using std::cout, std::cin, std::vector;

int NumTruck(int n, int k) {
  if (n <= k) {
    return 1;
  }
  return ((n % 2 == 0) ? 2 * NumTruck(n/2, k)
                       : NumTruck(n/2, k) + NumTruck(n/2 + 1, k));
}

int main() {
  int n;
  int k;
  cin >> n >> k;
  cout << NumTruck(n, k);
} 