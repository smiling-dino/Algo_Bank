#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

const int cMod = 1000000000;

struct Node {
  Node* ptr_to_parent = nullptr;
  Node* ptr_to_left_son = nullptr;
  Node* ptr_to_right_son = nullptr;
  int key = 0;
  int height = 1;
  Node(){};
  Node(int key) : key(key){};

  void SwithchValues(Node& other) { std::swap(this->key, other.key); }
  void RecalculateHeight() {
    this->height = 0;
    if (this->ptr_to_left_son != nullptr) {
      this->height = ptr_to_left_son->height;
    }
    if (this->ptr_to_right_son != nullptr) {
      this->height = std::max(ptr_to_right_son->height, this->height);
    }
    this->height++;
  }

  void FromLeftToRightBound() {
    if (ptr_to_left_son != nullptr) {
      Node* ptr_to_b = this->ptr_to_left_son;
      Node* ptr_to_alpha = this->ptr_to_left_son->ptr_to_left_son;
      Node* ptr_to_beta = this->ptr_to_left_son->ptr_to_right_son;
      Node* ptr_to_gamma = this->ptr_to_right_son;

      this->ptr_to_left_son = ptr_to_alpha;
      this->ptr_to_right_son = ptr_to_b;
      ptr_to_b->ptr_to_left_son = ptr_to_beta;
      ptr_to_b->ptr_to_right_son = ptr_to_gamma;
      this->SwithchValues(*ptr_to_b);

      ptr_to_b->RecalculateHeight();
      this->RecalculateHeight();

      if (ptr_to_alpha != nullptr) {
        ptr_to_alpha->ptr_to_parent = this;
      }
      if (ptr_to_gamma != nullptr) {
        ptr_to_gamma->ptr_to_parent = ptr_to_b;
      }
    }
  }

  void FromRightToLeftBound() {
    if (ptr_to_right_son != nullptr) {
      Node* ptr_to_b = this->ptr_to_right_son;
      Node* ptr_to_alpha = this->ptr_to_left_son;
      Node* ptr_to_beta = this->ptr_to_right_son->ptr_to_left_son;
      Node* ptr_to_gamma = this->ptr_to_right_son->ptr_to_right_son;

      this->ptr_to_left_son = ptr_to_b;
      this->ptr_to_right_son = ptr_to_gamma;
      ptr_to_b->ptr_to_left_son = ptr_to_alpha;
      ptr_to_b->ptr_to_right_son = ptr_to_beta;
      this->SwithchValues(*ptr_to_b);

      ptr_to_b->RecalculateHeight();
      this->RecalculateHeight();

      if (ptr_to_alpha != nullptr) {
        ptr_to_alpha->ptr_to_parent = ptr_to_b;
      }
      if (ptr_to_gamma != nullptr) {
        ptr_to_gamma->ptr_to_parent = this;
      }
    }
  }

  int Delta() const {
    int delta = 0;

    if (this->ptr_to_left_son != nullptr) {
      delta += ptr_to_left_son->height;
    }
    if (this->ptr_to_right_son != nullptr) {
      delta -= ptr_to_right_son->height;
    }
    return delta;
  }

  void Balance() {
    if (this->Delta() == -2) {
      if ((this->ptr_to_right_son != nullptr) &&
          (this->ptr_to_right_son->Delta() == 1)) {
        this->ptr_to_right_son->FromLeftToRightBound();
        this->FromRightToLeftBound();
      } else {
        this->FromRightToLeftBound();
      }
    }
    if (this->Delta() == 2) {
      if ((this->ptr_to_left_son != nullptr) &&
          (this->ptr_to_left_son->Delta() == -1)) {
        this->ptr_to_left_son->FromRightToLeftBound();
        this->FromLeftToRightBound();
      } else {
        this->FromLeftToRightBound();
      }
    }
    if (this->ptr_to_parent != nullptr) {
      ptr_to_parent->RecalculateHeight();
      ptr_to_parent->Balance();
    }
  }

  void Insert(Node& other) {
    if (this->key != other.key) {
      if (this->key < other.key) {
        if (this->ptr_to_right_son == nullptr) {
          this->ptr_to_right_son = &other;
          other.ptr_to_parent = this;
          this->RecalculateHeight();
          this->Balance();
        } else {
          this->ptr_to_right_son->Insert(other);
        }
      } else {
        if (this->key > other.key) {
          if (this->ptr_to_left_son == nullptr) {
            this->ptr_to_left_son = &other;
            other.ptr_to_parent = this;
            this->RecalculateHeight();
            this->Balance();
          } else {
            this->ptr_to_left_son->Insert(other);
          }
        }
      }
    }
  }
  int FindLowerBound(int number) const {
    if (number == this->key) {
      return number;
    }
    if (number > this->key) {
      if (ptr_to_right_son != nullptr) {
        return ptr_to_right_son->FindLowerBound(number);
      }
      return -1;
    }
    if (number < this->key) {
      if (ptr_to_left_son != nullptr) {
        int lower_bound_in_sub_tree = ptr_to_left_son->FindLowerBound(number);
        if (lower_bound_in_sub_tree != -1) {
          return lower_bound_in_sub_tree;
        }
      }
      return this->key;
    }
    return -1;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(0);

  int num_of_requests;
  std::cin >> num_of_requests;

  std::vector<Node*> nodes;
  Node* head = nullptr;
  int last_number = 0;
  bool last_was_insert = true;

  for (int i = 0; i < num_of_requests; i++) {
    std::string request;
    int number;
    std::cin >> request >> number;

    switch (request[0]) {
      case '?':
        last_was_insert = false;
        if (head != nullptr) {
          last_number = head->FindLowerBound(number);
        } else {
          last_number = -1;
        }
        std::cout << last_number << "\n";
        break;
      case '+':
        if (!last_was_insert) {
          number = (number + last_number) % cMod;
        }
        nodes.push_back(new Node(number));
        if (i == 0) {
          head = nodes.back();
        } else {
          if (head != nullptr) {
            head->Insert(*nodes.back());
          }
        }
        last_was_insert = true;
        break;
    }
  }
  for (size_t i = 0; i < nodes.size(); i++) {
    delete nodes[i];
  }
}