#include <algorithm>
#include <iostream>
#include <vector>

struct Work {
  int time_teacher_a = 0;
  int time_teacher_b = 0;
  int index;
};

bool Comparator(const Work& w1, const Work& w2) {
  if (std::min(w1.time_teacher_a, w2.time_teacher_b) ==
      std::min(w1.time_teacher_b, w2.time_teacher_a)) {
    return std::max(w1.time_teacher_a, w2.time_teacher_b) <
           std::max(w1.time_teacher_b, w2.time_teacher_a);
  }
  return std::min(w1.time_teacher_a, w2.time_teacher_b) <
         std::min(w1.time_teacher_b, w2.time_teacher_a);
}

int main() {
  int n_works;

  std::cin >> n_works;

  std::vector<Work> works(n_works);

  for (int i = 0; i < n_works; ++i) {
    works[i].index = i + 1;
    std::cin >> works[i].time_teacher_a;
  }

  for (int i = 0; i < n_works; ++i) {
    std::cin >> works[i].time_teacher_b;
  }

  std::sort(works.begin(), works.end(), Comparator);

  int time_a = 0;
  int time_b = 0;
  std::vector<int> order;
  for (Work w : works) {
    order.push_back(w.index);
    time_a += w.time_teacher_a;
    time_b = std::max(time_a, time_b) + w.time_teacher_b;
  }

  std::cout << time_b << "\n";
  for (int ind : order) {
    std::cout << ind << " ";
  }
  std::cout << "\n";
  for (int ind : order) {
    std::cout << ind << " ";
  }
}
// 2 0 1 3
// 1 2 1 3