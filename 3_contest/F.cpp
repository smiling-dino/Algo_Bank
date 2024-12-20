#include <math.h>

#include <algorithm>
#include <iostream>
#include <vector>

void Update(std::vector<int>& tree, int value) {
  tree[value]++;
  while (value > 1) {
    value /= 2;
    tree[value] = tree[2 * value] + tree[2 * value + 1];
  }
}

int Get(std::vector<int>& tree, int inddex, int left_bound, int right_bound,
        int left_request, int right_request) {
  if (left_bound >= left_request && right_bound <= right_request) {
    return tree[inddex];
  }

  if (left_bound >= right_request || right_bound <= left_request) {
    return 0;
  }

  int mid = (left_bound + right_bound) / 2;
  return Get(tree, 2 * inddex, left_bound, mid, left_request, right_request) +
         Get(tree, 2 * inddex + 1, mid, right_bound, left_request,
             right_request);
}

signed main() {
  int n;
  std::cin >> n;
  std::vector<int> compress;
  std::vector<std::pair<int, int>> segments(n);
  for (int i = 0; i < n; i++) {
    int a;
    int b;
    std::cin >> a >> b;
    a--;
    segments[i] = {a, b};
    compress.push_back(a);
    compress.push_back(b);
  }
  std::sort(compress.begin(), compress.end());
  compress.resize(unique(compress.begin(), compress.end()) - compress.begin());
  for (auto& i : segments) {
    i.first = lower_bound(compress.begin(), compress.end(), i.first) -
              compress.begin();
    i.second = lower_bound(compress.begin(), compress.end(), i.second) -
               compress.begin();
  }

  int nlog = 1 << (int)ceil(log2(compress.size()));
  std::vector<int> tree(2 * nlog);

  int q = segments.size();

  for (int i = 0; i < q; i++) {
    segments[i].second = -segments[i].second;
  }
  std::sort(segments.begin(), segments.end());
  std::reverse(segments.begin(), segments.end());
  std::pair<int, int> last = {-1, -1};
  long long ans = 0;
  long long counter = 0;
  for (int i = 0; i < q; i++) {
    if (segments[i] == last) {
      counter++;
    } else {
      counter = 0;
    }
    last = segments[i];

    int a = segments[i].first;
    int b = -segments[i].second;

    ans -= counter;
    ans += Get(tree, 1, 0, nlog, a + 1, b + 1);
    Update(tree, b + nlog);
  }

  std::cout << ans;
}
