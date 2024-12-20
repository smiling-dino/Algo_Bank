#include <iostream>
#include <vector>

const int cC1 = 123;
const int cC2 = 45;
const int cC3 = 10000000;
const int cC4 = 4321;

void Swap(std::vector<int>& v, int index_1, int index_2) {
  int temp_num = v[index_1];
  v[index_1] = v[index_2];
  v[index_2] = temp_num;
}

void Partition(std::vector<int>& v, int left_bound, int rigth_bound,
               int pivot) {
  int l = left_bound;
  int r = rigth_bound;
  while (l < r) {
    while (v[l] < pivot) {
      l++;
    }
    while (v[r] >= pivot) {
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
  while (v[l] < pivot) {
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

int LowerThanPivot(std::vector<int>& v, int left_bound, int rigth_bound,
                   int pivot) {
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

int EqualPivot(std::vector<int>& v, int left_bound, int rigth_bound,
               int pivot) {
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

int QuickSelect(std::vector<int>& v, int left_bound, int rigth_bound,
                int k_stat, bool determined);

int MedianOfMedian(std::vector<int>& v, int left_bound, int rigth_bound) {
  std::vector<int> median;
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

int QuickSelect(std::vector<int>& v, int left_bound, int rigth_bound,
                int k_stat, bool determined) {
  int pivot = 0;
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

int main() {
  int n;
  int k_stat;
  std::cin >> n >> k_stat;
  std::vector<int> num(n);
  if (n == 1) {
    int a_0;
    std::cin >> a_0;
    std::cout << a_0;
  } else {
    int a_0;
    int a_1;
    std::cin >> a_0 >> a_1;
    num[0] = a_0;
    num[1] = a_1;
    for (int i = 2; i < n; i++) {
      num[i] = (num[i - 1] * cC1 + num[i - 2] * cC2) % (cC3 + cC4);
    }
  }
  std::cout << QuickSelect(num, 0, num.size() - 1, k_stat, true) << '\n';
}