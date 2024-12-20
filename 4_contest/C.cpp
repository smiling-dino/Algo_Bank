#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

struct Node {
  Node* ptr_to_parent = nullptr;
  Node* ptr_to_left_son = nullptr;
  Node* ptr_to_right_son = nullptr;
  std::string prior;
  std::string key;
  int height = 1;
  Node(){};
  Node(std::string prior, std::string key) : prior(prior), key(key){};

  void SwithchValues(Node& other) {
    std::swap(this->key, other.key);
    std::swap(this->prior, other.prior);
  }
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
    if (this->prior != other.prior) {
      if (this->prior < other.prior) {
        if (this->ptr_to_right_son == nullptr) {
          this->ptr_to_right_son = &other;
          other.ptr_to_parent = this;
          this->RecalculateHeight();
          this->Balance();
        } else {
          this->ptr_to_right_son->Insert(other);
        }
      } else {
        if (this->prior > other.prior) {
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
  std::string FindStr(std::string searching) const {
    if (searching == this->prior) {
      return key;
    }
    if (searching > this->prior) {
      if (ptr_to_right_son != nullptr) {
        return ptr_to_right_son->FindStr(searching);
      }
      return "";
    }
    if (searching < this->prior) {
      if (ptr_to_left_son != nullptr) {
        return ptr_to_left_son->FindStr(searching);
      }
    }
    return "";
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(0);
  int num_of_requests;
  std::cin >> num_of_requests;
  static std::vector<Node> nodes_of_logins;
  static std::vector<Node> nodes_of_passwords;

  nodes_of_logins.reserve(num_of_requests);
  nodes_of_passwords.reserve(num_of_requests);
  Node head_of_logins;
  Node head_of_passwords;

  for (int i = 0; i < num_of_requests; i++) {
    std::string login;
    std::string password;
    std::cin >> login >> password;
    nodes_of_logins.push_back(Node(login, password));
    nodes_of_passwords.push_back(Node(password, login));

    if (i == 0) {
      head_of_logins = nodes_of_logins.back();
      head_of_passwords = nodes_of_passwords.back();

    } else {
      head_of_logins.Insert(nodes_of_logins.back());
      head_of_passwords.Insert(nodes_of_passwords.back());
    }
  }

  std::cin >> num_of_requests;
  for (int i = 0; i < num_of_requests; i++) {
    std::string searching;
    std::cin >> searching;
    std::string finded_password = head_of_passwords.FindStr(searching);
    std::string finded_login = head_of_logins.FindStr(searching);

    if ((!finded_login.empty()) || (!finded_password.empty())) {
      if (finded_password.empty()) {
        std::cout << finded_login << "\n";
      } else {
        std::cout << finded_password << "\n";
      }
    }
  }
}