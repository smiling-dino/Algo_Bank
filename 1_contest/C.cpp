#include <cstdint>
#include <iostream>
#include <vector>

const int cGroupsOfDigits = 256;
const int cNumOfDigits = 7;

void CountSort(std::vector<uint64_t>& vec, int digit) {
  std::vector<std::vector<uint64_t>> temp(cGroupsOfDigits);
  for (std::size_t i = 0; i < vec.size(); ++i) {
    uint64_t num = vec[i];
    uint8_t* index = (uint8_t*)&num;
    temp[index[digit]].push_back(vec[i]);
  }
  long long index = 0;
  for (std::size_t i = 0; i != temp.size(); ++i) {
    for (std::size_t j = 0; j < temp[i].size(); ++j) {
      vec[index] = temp[i][j];
      index++;
    }
  }
}

void LastDigitSort(std::vector<uint64_t>& vec) {
  for (int digit = 0; digit <= cNumOfDigits; ++digit) {
    CountSort(vec, digit);
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<uint64_t> vec(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> vec[i];
  }
  LastDigitSort(vec);
  for (uint64_t elem : vec) {
    std::cout << elem << " ";
  }
}