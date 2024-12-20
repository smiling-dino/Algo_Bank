#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

struct Window {
  long long sum = 0;
  std::deque<long long> arr;

  void Insert(int elem) {
    arr.push_back(elem);
    sum += elem;
  }

  void Delete() {
    sum -= arr.front();
    arr.pop_front();
  }

  long long GetSum() const { return sum; }

  void Clear() {
    sum = 0;
    arr.clear();
  }
};
struct Queue {
  std::vector<std::pair<long long, long long>> first_half;
  std::vector<std::pair<long long, long long>> second_half;
  int size_of_queue = 0;

  void Transmiss() {
    while (!first_half.empty()) {
      long long elem = first_half.back().first;
      first_half.pop_back();
      if (second_half.empty()) {
        second_half.push_back({elem, elem});
      } else {
        second_half.push_back(
            {elem, std::max(elem, second_half.back().second)});
      }
    }
  }

  void Insert(long long elem) {
    if (first_half.empty()) {
      first_half.push_back({elem, elem});
    } else {
      first_half.push_back({elem, std::max(elem, first_half.back().second)});
    }
    size_of_queue++;
  }

  long long Delete() {
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

  long long Front() {
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

  long long Max() {
    if (size_of_queue == 0) {
      std::cout << "error\n";
      return -1;
    }
    if (!first_half.empty() && !second_half.empty()) {
      return std::max(first_half.back().second, second_half.back().second);
    }
    if (!first_half.empty()) {
      return first_half.back().second;
    }
    return second_half.back().second;
  }
};

void InsertFirstN(Window& w, std::vector<long long>& vec, int n) {
  for (int i = 0; i < n; i++) {
    w.Insert(vec[i]);
  }
}

void InsertFirstN(Queue& q, std::vector<long long>& vec, int n) {
  for (int i = 0; i < n; i++) {
    q.Insert(vec[i]);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  long long sum_of_elem = 0;
  int n;
  std::cin >> n;
  std::vector<long long> vec(2 * n);
  for (int i = 0; i < n; i++) {
    std::cin >> vec[i];
    sum_of_elem += vec[i];
  }
  for (int i = n; i < 2 * n; i++) {
    vec[i] = vec[i - n];
  }
  std::vector<long long> sum(2 * n);
  int len_of_half = n / 2;
  Window w;
  InsertFirstN(w, vec, len_of_half);
  for (int i = len_of_half; i < 2 * n; i++) {
    sum[i - len_of_half] = w.GetSum();
    w.Delete();
    w.Insert(vec[i]);
  }
  std::vector<long long> choice_of_second(n, 0);
  w.Clear();
  Queue q;
  InsertFirstN(q, sum, n - len_of_half);
  for (int i = 1; i <= n; i++) {
    q.Delete();
    q.Insert(sum[i - len_of_half - 1 + n]);
    choice_of_second[i - 1] = q.Max();
  }
  long long min_element =
      *std::min_element(choice_of_second.begin(), choice_of_second.end());
  std::cout << sum_of_elem - min_element << " " << min_element;
}