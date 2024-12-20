#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using std::cout, std::cin;

bool SegmentCoverAllDots(std::vector<long int>& v, long int l, int k) {
  long int num_of_segmets = 1;
  long int right_bound = v[0] + l;
  for (long int elem : v) {
    if (elem > right_bound) {
      num_of_segmets++;
      right_bound = elem + l;
    }
  }
  return num_of_segmets <= k;
}

long int MinimalSegment(std::vector<long int>& v, int k) {
  long int r = (v.back() - v.front() + k - 1) / k;
  long int l = 0;
  while (r > l) {
    long int middle = (r + l) / 2;
    (SegmentCoverAllDots(v, middle, k)) ? r = middle : l = middle + 1;
  }
  return r;
}

int main() {
  int n;
  int k;
  cin >> n >> k;
  std::vector<long int> vec(n);
  for (int i = 0; i < n; i++) {
    cin >> vec[i];
  }
  std::sort(vec.begin(), vec.end());
  cout << MinimalSegment(vec, k) << std::endl;
}