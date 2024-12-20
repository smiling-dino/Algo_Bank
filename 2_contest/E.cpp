#include <iostream>
#include <string>
#include <vector>

bool IsRgihtPSP(std::string s) {
  std::vector<char> stack;
  for (char c : s) {
    if ((c == '(') || (c == '[') || (c == '{')) {
      stack.push_back(c);
    } else {
      if ((!stack.empty()) && (((c == ')') && (stack.back() == '(')) ||
                               ((c == ']') && (stack.back() == '[')) ||
                               ((c == '}') && (stack.back() == '{')))) {
        stack.pop_back();
      } else {
        return false;
      }
    }
  }
  return stack.empty();
}

int main() {
  std::string s;
  std::cin >> s;
  if (IsRgihtPSP(s)) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
}