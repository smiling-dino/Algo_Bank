#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

const int cUpperBoundOfelem = 2000000;

int Get(std::vector<std::vector<std::pair<int, int>>>& persistent_array,
        int version, int index) {
  index--;
  std::pair<int, int> search = {version, cUpperBoundOfelem};
  auto iterator = std::upper_bound(persistent_array[index].begin(),
                                   persistent_array[index].end(), search);
  iterator--;
  std::pair<int, int> finded = *iterator;
  return finded.second;
}

void Create(std::vector<std::vector<std::pair<int, int>>>& persistent_array,
            int template_version, int index, int value, int num_of_version) {
  index--;
  for (int i = 0; i < (int)persistent_array.size(); i++) {
    if (i == index) {
      persistent_array[i].push_back(std::make_pair(num_of_version, value));
      continue;
    }
    if (persistent_array[i].back().first > template_version) {
      persistent_array[i].push_back(std::make_pair(
          num_of_version, Get(persistent_array, template_version, i + 1)));
    }
  }
}

int main() {
  int num_of_numbers;
  std::cin >> num_of_numbers;
  std::vector<std::vector<std::pair<int, int>>> persistent_array(
      num_of_numbers, std::vector<std::pair<int, int>>(1));
  for (int i = 0; i < num_of_numbers; ++i) {
    std::cin >> persistent_array[i][0].second;
    persistent_array[i][0].first = 1;
  }

  int num_of_requests;
  std::cin >> num_of_requests;
  std::string s;
  int num_of_version = 1;
  for (int i = 0; i < num_of_requests; ++i) {
    std::cin >> s;
    int index;
    int version;
    switch (s[0]) {
      case 'c':
        int version_of_template;
        int value;
        std::cin >> version_of_template >> index >> value;
        num_of_version++;
        Create(persistent_array, version_of_template, index, value,
               num_of_version);
        break;
      case 'g':
        std::cin >> version >> index;
        std::cout << Get(persistent_array, version, index) << "\n";
        break;
    }
  }
}
