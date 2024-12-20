#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

const long long cArgInFormula = 1 << 30;

void Swap(std::vector<int>& heap, int pos_1, int pos_2);

void SiftUp(std::vector<int>& heap, int pos) {
  while ((pos != 0) && (heap[pos] < heap[(pos + 1) / 2 - 1])) {
    Swap(heap, pos, (pos + 1) / 2 - 1);
    pos = (pos + 1) / 2 - 1;
  }
}

void SiftDown(std::vector<int>& heap, std::size_t pos) {
  while ((heap.size() >= 2 * (pos + 1))) {
    int pos_to_min_kid = 2 * (pos + 1) - 1;
    if ((heap.size() >= 2 * (pos + 1) + 1) &&
        (heap[2 * (pos + 1) - 1] > heap[2 * (pos + 1) + 1 - 1])) {
      pos_to_min_kid = 2 * (pos + 1);
    }
    if (heap[pos_to_min_kid] < heap[pos]) {
      Swap(heap, pos, pos_to_min_kid);
      pos = pos_to_min_kid;
    } else {
      break;
    }
  }
}

void Insert(std::vector<int>& heap, long long elem) {
  heap.push_back(elem);
  SiftUp(heap, heap.size() - 1);
}

void ExtractMin(std::vector<int>& heap) {
  Swap(heap, 0, heap.size() - 1);
  heap.pop_back();
  heap.shrink_to_fit();
  SiftDown(heap, 0);
}

void Swap(std::vector<int>& heap, int pos_1, int pos_2) {
  long long tmp_elem = heap[pos_1];
  heap[pos_1] = heap[pos_2];
  heap[pos_2] = tmp_elem;
}

long long CalculateNext(long long prev_num, long long x, long long y) {
  return (x * prev_num + y) % cArgInFormula;
}

int main() {
  int n;
  std::size_t k;
  std::cin >> n >> k;
  std::vector<int> heap;
  std::vector<int> array_of_min;
  long long prev_num;
  long long x;
  long long y;
  int max_elem = -1;
  std::cin >> prev_num >> x >> y;
  for (int i = 0; i < n; i++) {
    int next_num = CalculateNext(prev_num, x, y);
    if (array_of_min.size() < k) {
      array_of_min.push_back(next_num);
      max_elem = std::max(max_elem, next_num);
    } else {
      if (max_elem > next_num) {
        *(std::max_element(array_of_min.begin(), array_of_min.end())) =
            next_num;
        max_elem =
            *(std::max_element(array_of_min.begin(), array_of_min.end()));
      }
    }
    prev_num = next_num;
  }
  for (std::size_t i = 0; i < k; i++) {
    Insert(heap, array_of_min[i]);
  }

  for (std::size_t i = 0; i < k; i++) {
    std::cout << heap[0] << " ";
    ExtractMin(heap);
  }
}