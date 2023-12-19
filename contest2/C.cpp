#include <deque>
#include <iostream>

class GoblinQueue {
  std::deque<int> first_half_;
  std::deque<int> second_half_;

  void Balance() {
    if (first_half_.size() < second_half_.size()) {
      first_half_.push_back(second_half_.front());
      second_half_.pop_front();
    }
    else if (first_half_.size() > second_half_.size() + 1) {
      second_half_.push_front(first_half_.back());
      first_half_.pop_back();
    }
  }
  
public:
  void PushBack(int goblin) {
    Balance();
    second_half_.push_back(goblin);
  }
  void PushMid(int goblin) {
    Balance();
    first_half_.push_back(goblin);
  }
  int PopFront() {
    Balance();
    int res = first_half_.front();
    first_half_.pop_front();
    return res;
  }
};

int main() {
  int num;
  std::cin >> num;
  GoblinQueue que;
  char req;
  int goblin;
  while (num-- > 0) {
    std::cin >> req;
    if (req == '+') {
      std::cin >> goblin;
      que.PushBack(goblin);
    } else if (req == '*') {
      std::cin >> goblin;
      que.PushMid(goblin);
    } else if (req == '-') {
      std::cout << que.PopFront() << '\n';
    }
  }

  return 0;
}