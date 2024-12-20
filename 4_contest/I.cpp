#include <iostream>
#include <string>
#include <vector>

int main() {
  int num_of_elements;
  int num_of_requests;
  std::cin >> num_of_elements >> num_of_requests;
  std::vector<int> numbers(num_of_elements);
  for (int i = 0; i < num_of_elements; i++) {
    std::cin >> numbers[i];
  }
  for (int i = 0; i < num_of_requests; i++) {
    std::string request;
    std::cin >> request;
    int left_bound;
    int right_bound;
    int x;
    int y;
    int result = 0;
    int index;
    int elem;
    switch (request[0]) {
      case 'G':
        std::cin >> left_bound >> right_bound >> x >> y;
        left_bound--;
        result = 0;
        for (int i = left_bound; i < right_bound; i++) {
          if ((numbers[i] >= x) && (numbers[i] <= y)) {
            result++;
          }
        }
        std::cout << result << "\n";
        break;

      case 'S':
        std::cin >> index >> elem;
        index--;
        numbers[index] = elem;
        break;
    }
  }
}