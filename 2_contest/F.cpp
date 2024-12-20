#include <iostream>
#include <string>
#include <vector>

int main() {
  std::string s;
  std::vector<long long> nums;
  while (std::cin >> s) {
    long long last_num = 0;
    switch (s[0]) {
      case '+':
        last_num = nums.back();
        nums.pop_back();
        nums.back() += last_num;
        break;

      case '*':
        last_num = nums.back();
        nums.pop_back();
        nums.back() *= last_num;
        break;

      case '-':
        last_num = nums.back();
        nums.pop_back();
        nums.back() -= last_num;
        break;

      default:
        nums.push_back(std::stoll(s));
        break;
    }
  }
  std::cout << nums.back();
}