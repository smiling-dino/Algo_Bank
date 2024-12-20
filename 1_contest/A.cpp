#include <iostream>
#include <vector>
void Merge(std::vector<std::vector<int>>& vec, int l_part_begin,
           int r_part_begin, int r_part_end) {
  std::vector<std::vector<int>> temp;
  int l_part_end = r_part_begin;
  int l = l_part_begin;
  int r = r_part_begin;
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
    if (vec[l][0] < vec[r][0]) {
      temp.push_back(vec[l]);
      l++;
    } else {
      temp.push_back(vec[r]);
      r++;
    }
  }
  for (int j = 0; j < (int)temp.size(); ++j) {
    vec[j + l_part_begin] = temp[j];
  }
}

void MergeSort(std::vector<std::vector<int>>& vec) {
  int size_of_part = 2;
  int length = (int)vec.size();
  if (length == 1) {
    return;
  }
  int old_out_of_frame = 0;
  while (length / size_of_part != 0) {
    for (int i = 0; i < length / size_of_part; ++i) {
      Merge(vec, i * size_of_part, i * size_of_part + size_of_part / 2,
            (i + 1) * size_of_part);
    }
    int new_out_of_frame = length % size_of_part;
    if (new_out_of_frame > old_out_of_frame) {
      Merge(vec, length - new_out_of_frame, length - old_out_of_frame, length);
      old_out_of_frame = new_out_of_frame;
    }
    size_of_part *= 2;
  }
  if (old_out_of_frame > 0) {
    Merge(vec, 0, length - old_out_of_frame, length);
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<std::vector<int>> points;
  for (int i = 1; i <= n; ++i) {
    std::vector<int> point(2);
    std::cin >> point[0] >> point[1];
    points.push_back(point);
  }
  MergeSort(points);
  std::vector<std::vector<int>> segments;
  segments.push_back(points[0]);
  for (auto point : points) {
    if (point[0] <= segments.back()[1]) {
      segments.back()[1] = std::max(segments.back()[1], point[1]);
    } else {
      segments.push_back(point);
    }
  }
  std::cout << segments.size() << "\n";
  for (auto segment : segments) {
    std::cout << segment[0] << " " << segment[1] << "\n";
  }
  return 0;
}