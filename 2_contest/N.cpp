#include <iostream>
#include <set>
#include <string>
#include <vector>

// using int = long long;

void Allocate(
    std::set<std::pair<long long, long long>>& memory_sorted_by_length,
    std::set<std::pair<long long, long long>>& memory_sorted_by_index,
    std::vector<std::pair<long long, long long>>& my_req, long long lmength,
    long long num_of_r) {
  if (memory_sorted_by_length.empty()) {
    std::cout << -1 << "\n";
    my_req[num_of_r] = std::make_pair(-1LL, -1LL);
    return;
  }
  std::pair<long long, long long> max_element =
      *memory_sorted_by_length.rbegin();
  if (max_element.first < lmength) {
    std::cout << -1 << "\n";
    my_req[num_of_r] = std::make_pair(-1LL, -1LL);
    return;
  }
  memory_sorted_by_length.erase(max_element);
  memory_sorted_by_index.erase({max_element.second, max_element.first});
  std::cout << max_element.second + 1 << "\n";
  if (max_element.first == lmength) {
    my_req[num_of_r] = {max_element.second, max_element.first};
  } else {
    std::pair<long long, long long> extracted_part = {lmength,
                                                      max_element.second};
    std::pair<long long, long long> remained_part = {
        max_element.first - lmength, max_element.second + lmength};
    memory_sorted_by_length.insert(remained_part);
    memory_sorted_by_index.insert({remained_part.second, remained_part.first});

    my_req[num_of_r] = {extracted_part.second, extracted_part.first};
  }
}
// using namespace std;

std::pair<int, int> SwapPair(std::pair<long long, long long> a) {
  return {a.second, a.first};
}

void Deallocate1(
    std::set<std::pair<long long, long long>>& memory_sorted_by_length,
    std::set<std::pair<long long, long long>>& memory_sorted_by_index,
    std::vector<std::pair<long long, long long>>& requests,
    long long num_of_request) {
  std::pair<long long, long long> extracted_part = requests[num_of_request];
  if (extracted_part == std::make_pair(-1LL, -1LL)) {
    return;
  }

  // pair<int,int> seg = {extracted_part.first,extracted_part.second};
  // auto it = memory_sorted_by_index.find(extracted_part);
  // if (it != memory_sorted_by_index.begin()){
  //   it--;
  //   if (*it =)
  // }


  memory_sorted_by_index.insert(extracted_part);
  memory_sorted_by_length.insert({extracted_part.second, extracted_part.first});
  auto it = memory_sorted_by_index.find(extracted_part);

  if (it != memory_sorted_by_index.begin()) {
    auto left_it = std::prev(it);
    if ((*left_it).first + (*left_it).second == extracted_part.first) {
      std::pair<long long, long long> new_element = {
          (*left_it).first, (*left_it).second + extracted_part.second};

      memory_sorted_by_length.erase({(*left_it).second, (*left_it).first});
      memory_sorted_by_index.erase(left_it);
      memory_sorted_by_index.erase(extracted_part);
      memory_sorted_by_length.erase(
          {extracted_part.second, extracted_part.first});

      memory_sorted_by_index.insert(new_element);
      memory_sorted_by_length.insert({new_element.second, new_element.first});

      extracted_part = new_element;
    }
  }
  it = memory_sorted_by_index.find(extracted_part);

  auto right_it = std::next(it);
  if (right_it != memory_sorted_by_index.end()) {
    if (extracted_part.first + extracted_part.second == (*right_it).first) {
      std::pair<long long, long long> new_element = {
          extracted_part.first, (*right_it).second + extracted_part.second};

      memory_sorted_by_length.erase({(*right_it).second, (*right_it).first});
      memory_sorted_by_length.erase(
          {extracted_part.second, extracted_part.first});
      memory_sorted_by_index.erase(right_it);
      memory_sorted_by_index.erase(extracted_part);

      memory_sorted_by_index.insert(new_element);
      memory_sorted_by_length.insert({new_element.second, new_element.first});
    }
  }
}


void Deallocate(
    std::set<std::pair<long long, long long>>& memory_sorted_by_length,
    std::set<std::pair<long long, long long>>& memory_sorted_by_index,
    std::vector<std::pair<long long, long long>>& requests,
    long long num_of_request) {
  std::pair<long long, long long> extracted_part = requests[num_of_request];
  if (extracted_part == std::make_pair(-1LL, -1LL)) {
    return;
  }

  std::pair<long long, long long> seg = {
      extracted_part.first, extracted_part.second + extracted_part.first};
  auto it = memory_sorted_by_index.find(extracted_part);
  if (it != memory_sorted_by_index.begin()) {
    it--;
    if ((*it).first + (*it).second == seg.first) {
      seg.first = (*it).first;
      memory_sorted_by_length.erase(SwapPair(*it));
      memory_sorted_by_index.erase(it);
    }
  }

  it = memory_sorted_by_index.find(extracted_part);
  it++;
  if (it != memory_sorted_by_index.end()) {
    if ((*it).first == seg.second) {
      seg.second = (*it).first + (*it).second;
      memory_sorted_by_length.erase(SwapPair(*it));
      memory_sorted_by_index.erase(it);
    }
  }

  memory_sorted_by_index.insert({seg.first, seg.second - seg.first});
  memory_sorted_by_length.insert({seg.second - seg.first, seg.first});
}

int main() {
  // freopen("a.in", "r", stdin);
  long long num_of_memory_cells;
  int n;
  std::cin >> num_of_memory_cells >> n;
  std::set<std::pair<long long, long long>> memory_sorted_by_length;
  std::set<std::pair<long long, long long>> memory_sorted_by_index;
  std::vector<std::pair<long long, long long>> requests(n);

  std::pair<long long, long long> first_elem = {num_of_memory_cells, 0};
  memory_sorted_by_length.insert(first_elem);
  first_elem = {0, num_of_memory_cells};
  memory_sorted_by_index.insert(first_elem);
  long long number_of_request = 0;
  while (number_of_request < n) {
    long long request;
    std::cin >> request;
    if (request > 0) {
      Allocate(memory_sorted_by_length, memory_sorted_by_index, requests,
               request, number_of_request);
    } else {
      Deallocate1(memory_sorted_by_length, memory_sorted_by_index, requests,
                 -request - 1);
    }
    number_of_request++;
  }
}