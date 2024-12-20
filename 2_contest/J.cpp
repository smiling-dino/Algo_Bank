#include <iostream>
#include <string>
#include <vector>

void Transmiss(std::vector<std::pair<int, int>>& first_half,
               std::vector<std::pair<int, int>>& second_half) {
  while (!first_half.empty()) {
    int elem = first_half.back().first;
    first_half.pop_back();
    if (second_half.empty()) {
      second_half.push_back({elem, elem});
    } else {
      second_half.push_back({elem, std::min(elem, second_half.back().second)});
    }
  }
}

void Insert(std::vector<std::pair<int, int>>& first_half, int elem) {
  if (first_half.empty()) {
    first_half.push_back({elem, elem});
  } else {
    first_half.push_back({elem, std::min(elem, first_half.back().second)});
  }
}

int main() {
  int n;
  std::vector<std::pair<int, int>> first_half;
  std::vector<std::pair<int, int>> second_half;
  std::cin >> n;
  int size_of_queue = 0;
  for (int i = 0; i < n; i++) {
    std::string operation;
    std::cin >> operation;
    switch (operation[0]) {
      case 'e':
        int new_elem;
        std::cin >> new_elem;
        size_of_queue++;
        Insert(first_half, new_elem);
        std::cout << "ok"
                  << "\n";
        break;
      case 'd':
        if (size_of_queue == 0) {
          std::cout << "error"
                    << "\n";
        } else {
          if (second_half.empty()) {
            Transmiss(first_half, second_half);
          }
          std::cout << second_half.back().first << "\n";
          second_half.pop_back();
          size_of_queue--;
        }
        break;
      case 'f':
        if (size_of_queue == 0) {
          std::cout << "error"
                    << "\n";
        } else {
          if (second_half.empty()) {
            Transmiss(first_half, second_half);
          }
          std::cout << second_half.back().first << "\n";
        }
        break;
      case 's':
        std::cout << size_of_queue << "\n";
        break;
      case 'c':
        first_half.clear();
        second_half.clear();
        size_of_queue = 0;
        std::cout << "ok"
                  << "\n";
        break;
      case 'm':
        if (size_of_queue == 0) {
          std::cout << "error"
                    << "\n";
        } else {
          if ((!first_half.empty()) && (!second_half.empty())) {
            std::cout << std::min(first_half.back().second,
                                  second_half.back().second)
                      << "\n";
          } else {
            if (!first_half.empty()) {
              std::cout << first_half.back().second << "\n";
            } else {
              std::cout << second_half.back().second << "\n";
            }
          }
        }
        break;
    }
  }
}