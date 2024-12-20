#include <iostream>

using std::cout, std::cin;

const long double cRightBound = 1000000000;
const long double cLeftBound = -1000000000;
const int cFor = 2000;
const int cPrec = 20;

long double Equation(int a, int b, int c, int d, long double x) {
  return a * x * x * x + b * x * x + c * x + d;
}

long double BinFinder(int a, int b, int c, int d) {
  long double l = cLeftBound;
  long double r = cRightBound;
  bool increasing;
  (Equation(a, b, c, d, cRightBound) > 0) ? increasing = true
                                          : increasing = false;
  long double middle = 0;
  for (int i = 0; i <= cFor; ++i) {
    middle = (l + r) / 2;
    long double eq_value = Equation(a, b, c, d, middle);
    if (eq_value > 0) {
      (increasing) ? r = middle : l = middle;
    } else {
      (increasing) ? l = middle : r = middle;
    }
  }
  return middle;
}
int main() {
  int a;
  int b;
  int c;
  int d;
  cin >> a >> b >> c >> d;
  cout.precision(cPrec);
  cout << std::fixed << BinFinder(a, b, c, d);
}
