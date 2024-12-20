#include <cmath>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

const int cIndexOfLetter = 9;

struct MinHeap {
  std::vector<int> heap;

  void Swap(int pos_1, int pos_2) {
    int tmp_elem = heap[pos_1];
    heap[pos_1] = heap[pos_2];
    heap[pos_2] = tmp_elem;
  }

  void SiftUp(int pos) {
    while (pos != 0 && heap[pos] < heap[(pos + 1) / 2 - 1]) {
      Swap(pos, (pos + 1) / 2 - 1);
      pos = (pos + 1) / 2 - 1;
    }
  }

  void SiftDown(std::size_t pos) {
    while (heap.size() >= 2 * (pos + 1)) {
      int pos_to_min_kid = 2 * (pos + 1) - 1;
      if (heap.size() >= 2 * (pos + 1) + 1 &&
          heap[2 * (pos + 1) - 1] > heap[2 * (pos + 1)]) {
        pos_to_min_kid = 2 * (pos + 1);
      }
      if (heap[pos_to_min_kid] < heap[pos]) {
        Swap(pos, pos_to_min_kid);
        pos = pos_to_min_kid;
      } else {
        break;
      }
    }
  }

  void Insert(int elem) {
    heap.push_back(elem);
    SiftUp(heap.size() - 1);
  }

  void ExtractMin() {
    if (heap.empty()) {
      std::cout << "error";
    }
    Swap(0, heap.size() - 1);
    heap.pop_back();
    SiftDown(0);
  }

  int GetMin() const {
    if (heap.empty()) {
      std::cout << "error";
    }
    return heap[0];
  }

  bool IsEmpty() const { return heap.empty(); }

  std::size_t Size() const { return heap.size(); }

  void Clear() { heap.clear(); }
};

struct MaxHeap {
  std::vector<int> heap;

  void Swap(int pos_1, int pos_2) {
    int tmp_elem = heap[pos_1];
    heap[pos_1] = heap[pos_2];
    heap[pos_2] = tmp_elem;
  }

  void SiftUp(int pos) {
    while (pos != 0 && heap[pos] < heap[(pos + 1) / 2 - 1]) {
      Swap(pos, (pos + 1) / 2 - 1);
      pos = (pos + 1) / 2 - 1;
    }
  }

  void SiftDown(std::size_t pos) {
    while (heap.size() >= 2 * (pos + 1)) {
      int pos_to_min_kid = 2 * (pos + 1) - 1;
      if (heap.size() >= 2 * (pos + 1) + 1 &&
          heap[2 * (pos + 1) - 1] > heap[2 * (pos + 1)]) {
        pos_to_min_kid = 2 * (pos + 1);
      }
      if (heap[pos_to_min_kid] < heap[pos]) {
        Swap(pos, pos_to_min_kid);
        pos = pos_to_min_kid;
      } else {
        break;
      }
    }
  }

  void Insert(int elem) {
    heap.push_back(-elem);
    SiftUp(heap.size() - 1);
  }

  void ExtractMax() {
    if (heap.empty()) {
      std::cout << "error";
    }
    Swap(0, heap.size() - 1);
    heap.pop_back();
    SiftDown(0);
  }

  int GetMax() const {
    if (heap.empty()) {
      std::cout << "error";
    }
    return (-heap[0]);
  }

  bool IsEmpty() const { return heap.empty(); }

  std::size_t Size() const { return heap.size(); }

  void Clear() { heap.clear(); }
};

void NormalizeMax(MaxHeap& max_heap, MaxHeap& tmp_max_heap) {
  while ((!tmp_max_heap.IsEmpty()) &&
         (tmp_max_heap.GetMax() == max_heap.GetMax())) {
    tmp_max_heap.ExtractMax();
    max_heap.ExtractMax();
  }
}

void NormalizeMin(MinHeap& min_heap, MinHeap& tmp_min_heap) {
  while ((!tmp_min_heap.IsEmpty()) &&
         (tmp_min_heap.GetMin() == min_heap.GetMin())) {
    tmp_min_heap.ExtractMin();
    min_heap.ExtractMin();
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  MinHeap min_heap;
  MaxHeap max_heap;
  MinHeap tmp_min_heap;
  MaxHeap tmp_max_heap;
  int size = 0;

  for (int i = 0; i < n; i++) {
    std::string request;
    std::cin >> request;
    switch (request[0]) {
      case 'i':
        size++;
        int elem;
        std::cin >> elem;
        min_heap.Insert(elem);
        max_heap.Insert(elem);
        std::cout << "ok"
                  << "\n";

        break;
      case 'e':
        if (size == 0) {
          std::cout << "error"
                    << "\n";
        } else {
          size--;
          int elem = 0;
          if (request[cIndexOfLetter] == 'i') {
            NormalizeMin(min_heap, tmp_min_heap);
            elem = min_heap.GetMin();
            tmp_max_heap.Insert(elem);
            min_heap.ExtractMin();
          } else {
            NormalizeMax(max_heap, tmp_max_heap);
            elem = max_heap.GetMax();
            tmp_min_heap.Insert(elem);
            max_heap.ExtractMax();
          }
          std::cout << elem << "\n";
        }
        break;
      case 'g':
        if (size == 0) {
          std::cout << "error"
                    << "\n";
        } else {
          if (request[5] == 'i') {
            NormalizeMin(min_heap, tmp_min_heap);
            std::cout << min_heap.GetMin() << "\n";
          } else {
            NormalizeMax(max_heap, tmp_max_heap);
            std::cout << max_heap.GetMax() << "\n";
          }
        }
        break;
      case 's': {
        std::cout << size << "\n";
        break;
      }
      case 'c': {
        max_heap.Clear();
        min_heap.Clear();
        tmp_max_heap.Clear();
        tmp_min_heap.Clear();
        size = 0;
        std::cout << "ok"
                  << "\n";
        break;
      }
    }
  }

  return 0;
}
