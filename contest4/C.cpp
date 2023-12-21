#include <iostream>
#include <random>
#include <string>
#include <utility>

std::mt19937 mt;

class Node {
 public:
  Node(const std::string& key, const std::string& value, unsigned priority)
      : key_(key), value_(value), priority_(priority) {}

  ~Node() {
    delete left_son_;
    delete right_son_;
  }

  static Node* Insert(Node* root, Node* node) {
    auto [left, right] = root->Split(node->key_);
    return Merge(left, Merge(node, right));
  }
  std::string* Get(const std::string& key_to_find) {
    if (key_ == key_to_find) {
      return &value_;
    }
    if (key_ > key_to_find) {
      if (left_son_ == nullptr) {
        return nullptr;
      }
      return left_son_->Get(key_to_find);
    }
    if (right_son_ == nullptr) {
      return nullptr;
    }
    return right_son_->Get(key_to_find);
  }

 private:
  static Node* Merge(Node* left, Node* right) {
    if (left == nullptr) {
      return right;
    }
    if (right == nullptr) {
      return left;
    }
    Node* root;
    if (left->priority_ <= right->priority_) {
      root = left;
      root->right_son_ = Merge(root->right_son_, right);
    } else {
      root = right;
      root->left_son_ = Merge(left, root->left_son_);
    }
    return root;
  }

  std::pair<Node*, Node*> Split(const std::string& sep, bool leq = true) {
    std::pair<Node*, Node*> res;
    if ((leq && key_ <= sep) || (!leq && key_ < sep)) {
      if (right_son_ != nullptr) {
        res = right_son_->Split(sep);
      } else {
        res = {nullptr, nullptr};
      }
      right_son_ = res.first;
      res.first = this;
    } else {
      if (left_son_ != nullptr) {
        res = left_son_->Split(sep);
      } else {
        res = {nullptr, nullptr};
      }
      left_son_ = res.second;
      res.second = this;
    }
    return res;
  }

  std::string key_;
  std::string value_;
  unsigned priority_;
  Node* left_son_ = nullptr;
  Node* right_son_ = nullptr;
};

int main() {
  size_t num;
  std::cin >> num;
  if (num == 0) {
    return 0;
  }
  Node* car_by_racer_root = nullptr;
  Node* racer_by_car_root = nullptr;
  bool empty = true;
  while (num-- > 0) {
    std::string racer;
    std::string car;
    std::cin >> racer >> car;
    unsigned priority = mt();
    Node* cbr = new Node(racer, car, priority);
    Node* rbc = new Node(car, racer, priority);
    if (!empty) {
      car_by_racer_root = Node::Insert(car_by_racer_root, cbr);
      racer_by_car_root = Node::Insert(racer_by_car_root, rbc);
    } else {
      car_by_racer_root = cbr;
      racer_by_car_root = rbc;
      empty = false;
    }
  }
  size_t qreq;
  std::cin >> qreq;
  while (qreq-- > 0) {
    std::string request;
    std::cin >> request;
    std::string* ans = car_by_racer_root->Get(request);
    if (ans != nullptr) {
      std::cout << *ans << '\n';
      continue;
    }
    ans = racer_by_car_root->Get(request);
    if (ans != nullptr) {
      std::cout << *ans << '\n';
    }
  }

  delete car_by_racer_root;
  delete racer_by_car_root;

  return 0;
}
