#include <math.h>

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
struct Node {
  int index_node_l = -1;
  int index_node_r = -1;
  int sum = 0;
  int sum_2 = 0;
  int add = 0;
  Node() = default;

  Node& Left(std::vector<Node>& nodes) {
    if (index_node_l == -1) {
      nodes.push_back(Node());
      index_node_l = nodes.size() - 1;
    }
    return nodes[index_node_l];
  }

  Node& Right(std::vector<Node>& nodes) {
    if (index_node_r == -1) {
      nodes.push_back(Node());
      index_node_r = nodes.size() - 1;
    }
    return nodes[index_node_r];
  }
};

void Push(std::vector<Node>& nodes, int index, int len) {
  Node v = nodes[index];
  v.Left(nodes);
  v.Right(nodes);
  if (v.add != 0) {
    v.Left(nodes).add += v.add;
    v.Left(nodes).sum += v.add * len / 2;
    v.Left(nodes).sum_2 = len / 2 * v.Left(nodes).sum;
    v.Right(nodes).add += v.add;
    v.Right(nodes).sum += v.add * len / 2;
    v.Right(nodes).sum_2 = len / 2 * v.Right(nodes).sum;
    v.add = 0;
  }
  nodes[index] = v; 
}

long long Get(std::vector<Node>& nodes, int index, int left_bound,
              int right_bound, int left_request, int right_request) {
  if (left_bound >= left_request && right_bound <= right_request) {
    return nodes[index].sum;
  }

  if (left_bound >= right_request || right_bound <= left_request) {
    return 0;
  }

  int mid = (left_bound + right_bound) / 2;
  Push(nodes, index, right_bound - left_bound);
  return Get(nodes, nodes[index].index_node_l, left_bound, mid, left_request,
             right_request) +
         Get(nodes, nodes[index].index_node_r, mid, right_bound, left_request,
             right_request);
}

int Update(std::vector<Node>& nodes, int index, int left_bound,
              int right_bound, int left_request, int right_request, int num) {
  if (left_bound >= left_request && right_bound <= right_request) {
    nodes[index].add += num;
    nodes[index].sum += num * (right_bound - left_bound);
    return 0;
  }
  if (left_bound >= right_request || right_bound <= left_request) {
    return 0;
  }

  int mid = (left_bound + right_bound) / 2;
  Push(nodes, index, right_bound - left_bound);
  Update(nodes, nodes[index].index_node_l, left_bound, mid, left_request,
             right_request, num);
  Update(nodes, nodes[index].index_node_r, mid, right_bound, left_request,
             right_request, num);
  nodes[index].sum = nodes[nodes[index].index_node_l].sum + nodes[nodes[index].index_node_r].sum;
  return 0;
}

void print(vector<Node>&nodes, int index){
  if (index == -1){
    cout << " ";
    return;
  }
  cout << nodes[index].sum << ":(";
  print(nodes,nodes[index].index_node_l);
  print(nodes,nodes[index].index_node_r);
  cout << ")";
}

int main() {
  freopen("in.txt","r",stdin);
  int num_of_requests;
  std::cin >> num_of_requests;
  std::vector<int> compress;
  vector<tuple<int,bool,int,int>> seg(2*num_of_requests);
  for (int i = 0; i < num_of_requests; i++) {
    int x1;
    int x2;
    int y1;
    int y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    seg[2*i] = {x1,true,y1,y2};
    seg[2*i+1] = {x2,false,y1,y2};
  }
  vector<Node> nodes(1);
  sort(seg.begin(),seg.end());
  int last = 0;
  long long ans = 0;
  for (auto& [pos,end,a,b] : seg)
  {
    cout << pos << " " << end << " " << a << " " << b << '\n';
    ans += (pos - last) * nodes[0].sum;
    print(nodes,0);
    cout << " " << nodes[0].sum << "\n";
    last = pos;
    if (end){
        Update(nodes,0,0,16,a,b,1);
    }
    else {
        Update(nodes,0,0,16,a,b,-1);
    } 

  }

  cout << ans;
  
  
}