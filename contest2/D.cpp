#include <deque>
#include <iostream>
#include <string>

class Hat {
 public:
  void Enqueue(int iq) {
    que_.push_back(iq);
    while (!mins_.empty() && mins_.back() > iq) {
      mins_.pop_back();
    }
    mins_.push_back(iq);
  }
  int Dequeue() {
    if (que_.empty()) {
      return 0;
    }
    int res = que_.front();
    if (mins_.front() == que_.front()) {
      mins_.pop_front();
    }
    que_.pop_front();
    return res;
  }
  int Front() {
    if (que_.empty()) {
      return 0;
    }
    return que_.front();
  }
  int Size() {
    return que_.size();
  }
  void Clear() {
    que_.clear();
    mins_.clear();
  }
  int Min() {
    if (mins_.empty()) {
      return 0;
    }
    return mins_.front();
  }

 private:
  std::deque<int> que_;
  std::deque<int> mins_;
};

int main() {
  int requests_num;
  std::cin >> requests_num;
  Hat hat;
  std::string cmd;
  int iq;
  while (requests_num-- > 0) {
    std::cin >> cmd;

    if (cmd == "enqueue") {
      std::cin >> iq;
      hat.Enqueue(iq);
      std::cout << "ok\n";

    } else if (cmd == "dequeue") {
      int res = hat.Dequeue();
      if (res == 0) {
        std::cout << "error\n";
      } else {
        std::cout << res << '\n';
      }
    } else if (cmd == "front") {
      int res = hat.Front();
      if (res == 0) {
        std::cout << "error\n";
      } else {
        std::cout << res << '\n';
      }
    } else if (cmd == "size") {
      std::cout << hat.Size() << '\n';
    } else if (cmd == "clear") {
      hat.Clear();
      std::cout << "ok\n";
    }
    else if (cmd == "min") {
      int res = hat.Min();
      if (res == 0) {
        std::cout << "error\n";
      } else {
        std::cout << res << '\n';
      }
    }
  }

  return 0;
}