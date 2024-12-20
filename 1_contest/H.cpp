#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int num_sheeps;
  int num_dogs;
  std::cin >> num_sheeps >> num_dogs;
  std::vector<std::pair<int, int>> dogs(num_dogs);
  std::vector<std::pair<int, int>> sheeps(num_sheeps);

  for (int i = 0; i < num_sheeps; i++) {
    std::cin >> sheeps[i].first;
    sheeps[i].second = i;
  }
  for (int i = 0; i < num_dogs; i++) {
    std::cin >> dogs[i].first;
    dogs[i].second = i;
  }

  std::sort(dogs.begin(), dogs.end());
  std::sort(sheeps.begin(), sheeps.end());

  int pnt_sheep = 0;
  int l_dogs = 0;
  int r_dogs = num_dogs / 2;
  int sum = 0;
  std::vector<std::vector<int>> log;
  while ((pnt_sheep < num_sheeps) && (r_dogs < num_dogs)) {
    if (sheeps[pnt_sheep].first >= dogs[r_dogs].first) {
      r_dogs++;
    }
    if (sheeps[pnt_sheep].first <= dogs[l_dogs].first) {
      pnt_sheep++;
    }
    if ((r_dogs >= num_dogs) || (pnt_sheep >= num_sheeps)) {
      break;
    }
    if ((dogs[l_dogs].first < sheeps[pnt_sheep].first) &&
        (sheeps[pnt_sheep].first < dogs[r_dogs].first)) {
      std::vector<int> arr(3);
      arr[0] = sheeps[pnt_sheep].second;
      arr[1] = dogs[l_dogs].second;
      arr[2] = dogs[r_dogs].second;
      log.push_back(arr);
      r_dogs++;
      l_dogs++;
      pnt_sheep++;
      sum++;
    }
  }

  std::cout << sum << "\n";
  for (int i = 0; i < (int)log.size(); i++) {
    std::cout << (log[i][0] + 1) << " " << (log[i][1] + 1) << " "
              << (log[i][2] + 1) << "\n";
  }
}