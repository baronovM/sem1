#include <algorithm>
#include <iostream>
#include <vector>

class Node {
 public:
  Node(int tl, int tr)
      : count_(tr - tl + 1), tl_(tl), tm_((tl + tr) / 2), tr_(tr) {}

  ~Node() {
    delete left_son_;
    delete right_son_;
  }

  int GetAns() const { return tr_ - tl_ + 1 - ((min_ == 0) ? count_ : 0); }

  void Update(int left, int right, int delta) {
    if (tl_ == left && tr_ == right) {
      min_ += delta;
      assign_ += (tl_ != tr_ ? delta : 0);
      return;
    }
    if (left_son_ == nullptr) {
      left_son_ = new Node(tl_, tm_);
    }
    if (right_son_ == nullptr) {
      right_son_ = new Node(tm_ + 1, tr_);
    }

    if (assign_ != 0) {
      left_son_->Update(tl_, tm_, assign_);
      right_son_->Update(tm_ + 1, tr_, assign_);
      assign_ = 0;
    }

    if (left <= tm_) {
      left_son_->Update(left, std::min(tm_, right), delta);
    }
    if (right >= tm_ + 1) {
      right_son_->Update(std::max(tm_ + 1, left), right, delta);
    }

    if (left_son_->min_ < right_son_->min_) {
      min_ = left_son_->min_;
      count_ = left_son_->count_;
    } else if (left_son_->min_ > right_son_->min_) {
      min_ = right_son_->min_;
      count_ = right_son_->count_;
    } else {
      min_ = left_son_->min_;
      count_ = left_son_->count_ + right_son_->count_;
    }
  }
  
 private:
  int min_ = 0;
  int count_;
  int assign_ = 0;
  int tl_;
  int tm_;
  int tr_;
  Node* left_son_ = nullptr;
  Node* right_son_ = nullptr;
};

struct Event {
  int coord_x;
  bool is_rect_begin;
  int y1;
  int y2;
};

bool operator<(const Event& left, const Event& right) {
  return left.coord_x < right.coord_x;
}

int main() {
  int rect_number;
  std::cin >> rect_number;
  std::vector<Event> events;
  events.reserve(2 * rect_number);
  for (int i = 0; i < rect_number; ++i) {
    int x1;
    int y1;
    int x2;
    int y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    events.push_back({x1, true, y1, y2});
    events.push_back({x2, false, y1, y2});
  }

  std::sort(events.begin(), events.end());

  const int kMaxCoord = 8;
  Node* tree_root = new Node(0, kMaxCoord);
  int prev_x = 0;
  long long ans = 0;
  for (int i = 0; i < 2 * rect_number; ++i) {
    ans += (long long)(tree_root->GetAns()) * (events[i].coord_x - prev_x);
    prev_x = events[i].coord_x;
    if (events[i].y1 != events[i].y2) {
      tree_root->Update(events[i].y1, events[i].y2 - 1,
                        events[i].is_rect_begin ? 1 : -1);
    }
  }
  std::cout << ans;
  delete tree_root;
}