#include <cmath>
#include <iostream>
#include <string>
#include <vector>

void Swap(std::vector<std::pair<long long, int>>& heap,
          std::vector<int>& request, int pos_1, int pos_2);

void SiftUp(std::vector<std::pair<long long, int>>& heap,
            std::vector<int>& request, int pos) {
  if (pos == 1) {
    return;
  }
  if (heap[pos - 1].first < heap[pos / 2 - 1].first) {
    Swap(heap, request, pos - 1, pos / 2 - 1);
    SiftUp(heap, request, pos / 2);
  }
}

void SiftDown(std::vector<std::pair<long long, int>>& heap,
              std::vector<int>& request, std::size_t pos) {
  if (heap.size() < 2 * pos) {
    return;
  }
  int pos_to_min_kid = 2 * pos;
  if ((heap.size() >= 2 * pos + 1) &&
      (heap[2 * pos - 1].first > heap[2 * pos].first)) {
    pos_to_min_kid = 2 * pos + 1;
  }
  if (heap[pos_to_min_kid - 1].first < heap[pos - 1].first) {
    Swap(heap, request, pos - 1, pos_to_min_kid - 1);
    SiftDown(heap, request, pos_to_min_kid);
  }
}

void DecreaseKey(std::vector<std::pair<long long, int>>& heap,
                 std::vector<int>& requests) {
  int num_of_request;
  int delta;
  std::cin >> num_of_request >> delta;

  int position = requests[num_of_request - 1];
  heap[position].first -= delta;
  SiftUp(heap, requests, position + 1);
}

void Insert(std::vector<std::pair<long long, int>>& heap,
            std::vector<int>& requests, int num_of_request) {
  int num;
  std::cin >> num;
  std::pair<int, int> node = {num, num_of_request};
  heap.push_back(node);
  requests[num_of_request] = heap.size() - 1;
  SiftUp(heap, requests, heap.size());
}

void ExtractMin(std::vector<std::pair<long long, int>>& heap,
                std::vector<int>& requests) {
  Swap(heap, requests, 0, heap.size() - 1);
  heap.pop_back();
  SiftDown(heap, requests, 1);
}

void Swap(std::vector<std::pair<long long, int>>& heap,
          std::vector<int>& request, int pos_1, int pos_2) {
  std::pair<long long, int> tmp_elem = heap[pos_1];
  request[heap[pos_1].second] = pos_2;
  request[heap[pos_2].second] = pos_1;
  heap[pos_1] = heap[pos_2];
  heap[pos_2] = tmp_elem;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  std::vector<std::pair<long long, int>> heap;
  std::vector<int> requests(n);
  for (int i = 0; i < n; i++) {
    std::string request;
    std::cin >> request;
    switch (request[0]) {
      case 'i':
        Insert(heap, requests, i);

        break;
      case 'e':
        ExtractMin(heap, requests);
        break;
      case 'g':
        std::cout << heap[0].first << "\n";
        break;
      case 'd':
        DecreaseKey(heap, requests);
        break;
    }
  }
}