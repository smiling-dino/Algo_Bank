#include <algorithm>
#include <iostream>
#include <vector>

const int cMaxDay = 10;

void TraceFromCombination(std::vector<int>& tracks, std::vector<int>& cargo,
                          std::vector<int>& combination) {
  std::vector<std::vector<int>> trace;
  int index = 0;
  int cargo_in_track = tracks[index];
  std::vector<int> nul;
  trace.push_back(nul);
  for (int item : combination) {
    while (true) {
      if (cargo_in_track >= cargo[item]) {
        cargo_in_track -= cargo[item];
        trace.back().push_back(item + 1);
        trace.back().push_back(index + 1);
        break;
      }
      index++;
      if (index >= (int)tracks.size()) {
        index = 0;
        trace.push_back(nul);
      }
      cargo_in_track = tracks[index];
    }
  }

  for (auto item : trace) {
    std::cout << ((int)item.size() / 2) << " ";
    for (auto elem : item) {
      std::cout << elem << " ";
    }
  }
  std::cout << '\n';
}

int DaysFromCombination(std::vector<int>& tracks, std::vector<int>& cargo,
                        std::vector<int>& combination) {
  int days = 1;
  int index = 0;
  int cargo_in_track = tracks[index];
  for (int item : combination) {
    while (true) {
      if (cargo_in_track >= cargo[item]) {
        cargo_in_track -= cargo[item];
        break;
      }
      index++;
      if (index >= (int)tracks.size()) {
        days++;
        index = 0;
      }
      cargo_in_track = tracks[index];
    }
  }
  return days;
}

void MinimalDays(std::vector<int>& tracks, std::vector<int>& cargo) {
  if (*std::max_element(tracks.begin(), tracks.end()) <
      *std::max_element(cargo.begin(), cargo.end())) {
    std::cout << -1 << '\n';
    return;
  }
  std::vector<int> comb;
  for (int i = 0; i < (int)cargo.size(); i++) {
    comb.push_back(i);
  }
  std::vector<int> minimal_comb;
  int minimum_days = cMaxDay;
  do {
    int days_for_comb = DaysFromCombination(tracks, cargo, comb);
    if (minimum_days > days_for_comb) {
      minimum_days = days_for_comb;
      minimal_comb = comb;
    }
  } while (std::next_permutation(comb.begin(), comb.end()));
  std::cout << minimum_days << '\n';
  TraceFromCombination(tracks, cargo, minimal_comb);
}

int main() {
  int num_tracks;
  int num_cargo;
  while (std::cin >> num_tracks >> num_cargo) {
    std::vector<int> tracks(num_tracks);
    std::vector<int> cargo(num_cargo);
    for (int i = 0; i < num_tracks; ++i) {
      std::cin >> tracks[i];
    }
    for (int i = 0; i < num_cargo; ++i) {
      std::cin >> cargo[i];
    }
    MinimalDays(tracks, cargo);
  }
}