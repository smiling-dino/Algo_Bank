#include <iostream>
#include <vector>
unsigned long int MergeAndCountPermutation(std::vector<int>& vec,
                                           int l_part_begin, int r_part_begin,
                                           int r_part_end) {
  std::vector<int> temp;
  int l_part_end = r_part_begin;
  int l = l_part_begin;
  int r = r_part_begin;
  unsigned long int permutation = 0;
  while ((l < l_part_end) || (r < r_part_end)) {
    if (l == l_part_end) {
      temp.push_back(vec[r]);
      r++;
      continue;
    }
    if (r == r_part_end) {
      temp.push_back(vec[l]);
      l++;
      continue;
    }
    if (vec[l] > vec[r]) {
      temp.push_back(vec[l]);
      l++;
      permutation += (r_part_end - r);
    } else {
      temp.push_back(vec[r]);
      r++;
    }
  }
  for (int j = 0; j < (int)temp.size(); ++j) {
    vec[j + l_part_begin] = temp[j];
  }
  return permutation;
}

unsigned long int CountPermutation(std::vector<int>& vec) {
  int size_of_part = 2;
  int length = (int)vec.size();
  unsigned long int permutation = 0;
  if (length == 1) {
    return 0;
  }
  int old_out_of_frame = 0;
  while (length / size_of_part != 0) {
    for (int i = 0; i < length / size_of_part; ++i) {
      permutation += MergeAndCountPermutation(
          vec, i * size_of_part, i * size_of_part + size_of_part / 2,
          (i + 1) * size_of_part);
    }
    int new_out_of_frame = length % size_of_part;
    if (new_out_of_frame > old_out_of_frame) {
      permutation += MergeAndCountPermutation(
          vec, length - new_out_of_frame, length - old_out_of_frame, length);
      old_out_of_frame = new_out_of_frame;
    }
    size_of_part *= 2;
  }
  if (old_out_of_frame > 0) {
    permutation +=
        MergeAndCountPermutation(vec, 0, length - old_out_of_frame, length);
  }
  return permutation;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> nums(n);
  for (int i = 1; i <= n; ++i) {
    std::cin >> nums[i - 1];
  }
  std::cout << CountPermutation(nums);
  return 0;
}