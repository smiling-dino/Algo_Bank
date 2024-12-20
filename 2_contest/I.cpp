#include <deque>
#include <iostream>

void Normalize(std::deque<int>& first_half, std::deque<int>& second_half) {
  if (first_half.size() > second_half.size() + 1) {
    second_half.push_back(first_half.front());
    first_half.pop_front();
  }
}

int main() {
  int n;
  std::deque<int> first_half;
  std::deque<int> second_half;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    char operation;
    std::cin >> operation;
    int num = 0;
    switch (operation) {
      case '+':
        std::cin >> num;
        first_half.push_back(num);
        Normalize(first_half, second_half);
        break;

      case '-':
        if (second_half.empty()) {
          second_half.push_back(first_half.front());
          first_half.pop_front();
        }
        std::cout << second_half.front() << "\n";
        second_half.pop_front();
        Normalize(first_half, second_half);
        break;

      case '*':
        std::cin >> num;
        if (second_half.size() == first_half.size()) {
          first_half.push_front(num);
        } else {
          second_half.push_back(first_half.front());
          first_half.pop_front();
          first_half.push_front(num);
        }
    }
  }
}