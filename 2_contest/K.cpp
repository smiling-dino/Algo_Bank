#include <iostream>
#include <string>
#include <vector>

struct Queue {
  std::vector<std::pair<int, int>> first_half;
  std::vector<std::pair<int, int>> second_half;
  int size_of_queue = 0;

  void Transmiss() {
    while (!first_half.empty()) {
      int elem = first_half.back().first;
      first_half.pop_back();
      if (second_half.empty()) {
        second_half.push_back({elem, elem});
      } else {
        second_half.push_back(
            {elem, std::min(elem, second_half.back().second)});
      }
    }
  }

  void Insert(int elem) {
    if (first_half.empty()) {
      first_half.push_back({elem, elem});
    } else {
      first_half.push_back({elem, std::min(elem, first_half.back().second)});
    }
    size_of_queue++;
  }

  int Delete() {
    if (size_of_queue == 0) {
      std::cout << "error\n";
      return -1;
    }
    if (second_half.empty()) {
      Transmiss();
    }
    int elem = second_half.back().first;
    second_half.pop_back();
    size_of_queue--;
    return elem;
  }

  int Front() {
    if (size_of_queue == 0) {
      std::cout << "error\n";
      return -1;
    }
    if (second_half.empty()) {
      Transmiss();
    }
    return second_half.back().first;
  }

  void Size() const { std::cout << size_of_queue << "\n"; }

  void Clear() {
    first_half.clear();
    second_half.clear();
    size_of_queue = 0;
  }

  int Min() {
    if (size_of_queue == 0) {
      std::cout << "error\n";
      return -1;
    }
    if (!first_half.empty() && !second_half.empty()) {
      return std::min(first_half.back().second, second_half.back().second);
    }
    if (!first_half.empty()) {
      return first_half.back().second;
    }
    return second_half.back().second;
  }
};

void InsertHorizontalSubArrayInQueue(Queue& q,
                                     std::vector<std::vector<int>>& arr, int i,
                                     int k) {
  for (int j = 0; j < k; j++) {
    q.Insert(arr[i][j]);
  }
}

void InsertVerticalSubArrayInQueue(Queue& q, std::vector<std::vector<int>>& arr,
                                   int j, int k) {
  for (int i = 0; i < k; i++) {
    q.Insert(arr[i][j]);
  }
}

int main() {
  int n;
  int k;
  std::cin >> n >> k;
  std::vector<std::vector<int>> matrix(n);
  std::vector<std::vector<int>> answer(n, std::vector<int>(n));

  for (int i = 0; i < n; i++) {
    matrix[i].resize(n);
    for (int j = 0; j < n; j++) {
      std::cin >> matrix[i][j];
    }
  }

  for (int i = 0; i < n; i++) {
    Queue q;
    InsertHorizontalSubArrayInQueue(q, matrix, i, k);
    answer[i][0] = q.Min();
    for (int j = k; j < n; j++) {
      q.Delete();
      q.Insert(matrix[i][j]);
      answer[i][j - k + 1] = q.Min();
    }
    q.Clear();
  }

  for (int j = 0; j < n; j++) {
    Queue q;
    InsertVerticalSubArrayInQueue(q, answer, j, k);
    answer[0][j] = q.Min();
    for (int i = k; i < n; i++) {
      q.Delete();
      q.Insert(answer[i][j]);
      answer[i - k + 1][j] = q.Min();
    }
  }

  for (int i = 0; i <= n - k; i++) {
    for (int j = 0; j <= n - k; j++) {
      std::cout << answer[i][j] << " ";
    }
    std::cout << "\n";
  }
}