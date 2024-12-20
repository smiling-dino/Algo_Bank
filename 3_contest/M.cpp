#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

const int cUpperBoundOfelem = 2000000;
const size_t cPodgon = 100000000;

int Get(std::vector<std::vector<std::pair<int, int>>>& persistent_array,
        int version, int index) {
  index--;
  std::pair<int, int> search = {version, cUpperBoundOfelem};
  auto iterator = std::upper_bound(persistent_array[index].begin(),
                                   persistent_array[index].end(), search);
  iterator--;
  return (*iterator).second;
}

void CreateBig(std::vector<std::vector<std::pair<int, int>>>& persistent_array,
               std::vector<int>& changes, int template_version, int index,
               int value, int num_of_version) {
  std::set<int> changes_without_repits;
  for (int i = template_version; i < num_of_version - 1; i++) {
    changes_without_repits.insert(changes[i]);
  }

  index--;

  for (int i : changes_without_repits) {
    if ((i != index) && (i != -1)) {
      persistent_array[i].push_back(std::make_pair(
          num_of_version, Get(persistent_array, template_version, i + 1)));
    }
  }
  persistent_array[index].push_back(std::make_pair(num_of_version, value));
}

void CreateSmall(
    std::vector<std::vector<std::pair<int, int>>>& persistent_array,
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
  std::vector<std::vector<std::pair<int, int>>> persistent_array;

  std::vector<int> changes(1, -1);
  for (int i = 0; i < num_of_numbers; ++i) {
    int elem;
    std::cin >> elem;
    std::vector<std::pair<int, int>> tmp;
    tmp.push_back(std::make_pair(1, elem));
    persistent_array.push_back(tmp);
  }

  int num_of_requests = 0;
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
        if (persistent_array.size() < cPodgon) {
          CreateSmall(persistent_array, version_of_template, index, value,
                      num_of_version);
        } else {
          CreateBig(persistent_array, changes, version_of_template, index,
                    value, num_of_version);
        }
        changes.push_back(--index);
        break;
      case 'g':
        std::cin >> version >> index;
        std::cout << Get(persistent_array, version, index) << "\n";
        break;
    }
  }
}
