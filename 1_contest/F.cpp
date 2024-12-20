#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

const int cMagicNumber = 8;

void Swap(std::vector<uint32_t>& v, int index_1, int index_2) {
  uint32_t temp_num = v[index_1];
  v[index_1] = v[index_2];
  v[index_2] = temp_num;
}

void Partition(std::vector<uint32_t>& v, int left_bound, int rigth_bound,
               uint32_t pivot) {
  int l = left_bound;
  int r = rigth_bound;
  while (l < r) {
    while ((v[l] < pivot) && (l <= rigth_bound)) {
      l++;
    }
    while ((v[r] >= pivot) && (r >= left_bound)) {
      r--;
    }
    if (l < r) {
      Swap(v, l, r);
      l++;
      r--;
    }
  }
  l = left_bound;
  r = rigth_bound;
  while ((v[l] < pivot) && (l <= rigth_bound)) {
    l++;
  }
  int l_start_equal = l;
  int r_new = r;
  while (r >= l_start_equal) {
    if (v[r] != pivot) {
      v[r_new] = v[r];
      r_new--;
    }
    r--;
  }
  while (r_new >= l_start_equal) {
    v[r_new] = pivot;
    r_new--;
  }
}

int LowerThanPivot(std::vector<uint32_t>& v, int left_bound, int rigth_bound,
                   uint32_t pivot) {
  int counter = 0;
  int index = left_bound;
  while (index <= rigth_bound) {
    if (v[index] < pivot) {
      counter++;
      index++;
    }
    if (v[index] >= pivot) {
      break;
    }
  }
  return counter;
}

int EqualPivot(std::vector<uint32_t>& v, int left_bound, int rigth_bound,
               uint32_t pivot) {
  int counter = 0;
  int index = left_bound;
  while (index <= rigth_bound) {
    if (v[index] == pivot) {
      counter++;
    }
    if (v[index] > pivot) {
      break;
    }
    index++;
  }
  return counter;
}

int QuickSelect(std::vector<uint32_t>& v, int left_bound, int rigth_bound,
                int k_stat, bool determined);

int MedianOfMedian(std::vector<uint32_t>& v, int left_bound, int rigth_bound) {
  std::vector<uint32_t> median;
  int index = left_bound;
  while (index <= rigth_bound) {
    if (rigth_bound - index < 4) {
      median.push_back(QuickSelect(v, index, rigth_bound,
                                   (rigth_bound - index) / 2 + 1, false));
      break;
    }
    median.push_back(QuickSelect(v, index, index + 4, 3, false));
    index += 5;
  }
  return QuickSelect(median, 0, (int)median.size() - 1, (median.size() + 1) / 2,
                     false);
}

int QuickSelect(std::vector<uint32_t>& v, int left_bound, int rigth_bound,
                int k_stat, bool determined) {
  uint32_t pivot = 0;
  if (v.size() < 5) {
    determined = false;
  }
  if (rigth_bound - left_bound == 0) {
    return v[left_bound];
  }
  if (determined) {
    pivot = MedianOfMedian(v, left_bound, rigth_bound);
  } else {
    pivot = v[rigth_bound];
  }
  Partition(v, left_bound, rigth_bound, pivot);
  int a = LowerThanPivot(v, left_bound, rigth_bound, pivot);
  int b = EqualPivot(v, left_bound, rigth_bound, pivot);
  if (k_stat <= a) {
    return QuickSelect(v, left_bound, left_bound + a - 1, k_stat, determined);
  }
  if ((a < k_stat) && (k_stat <= a + b)) {
    return pivot;
  }
  return QuickSelect(v, left_bound + a + b, rigth_bound, k_stat - a - b,
                     determined);
}

uint32_t cur = 0;
int a = 0;
int b = 0;

uint32_t NextRand24() {
  cur = cur * a + b;
  return cur >> cMagicNumber;
}

uint32_t NextRand32() {
  uint32_t x = NextRand24();
  uint32_t y = NextRand24();
  return (x << cMagicNumber) ^ y;
}

int main() {
  int n;
  std::cin >> n;

  std::cin >> a >> b;

  std::vector<uint32_t> num;

  for (int i = 0; i < n; i++) {
    num.push_back(NextRand32());
  }
  
  for (uint32_t elem : num)
  {
    std::cout << elem << " ";
  }
  std::cout << "\n";
  



  long long median =
      QuickSelect(num, 0, num.size() - 1, (num.size() + 1) / 2, false) << '\n';

  uint64_t sum = 0;
  for (uint32_t elem : num) {
    sum += std::abs((long long)elem - median);
  }
  std::cout << sum << "\n";
}