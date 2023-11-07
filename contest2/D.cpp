#include <deque>
#include <iostream>
#include <string>

int main() {
  int requests_num;
  std::cin >> requests_num;
  std::deque<int> que;
  std::deque<int> mins;
  std::string cmd;
  int iq;
  while (requests_num-- > 0) {
    std::cin >> cmd;

    if (cmd == "enqueue") {
      std::cin >> iq;
      que.push_back(iq);
      while (!mins.empty() && mins.back() > iq) {
        mins.pop_back();
      }
      mins.push_back(iq);
      std::cout << "ok\n";

    } else if (cmd == "dequeue") {
      if (que.empty()) {
        std::cout << "error\n";
        continue;
      }
      std::cout << que.front() << '\n';
      if (mins.front() == que.front()) {
        mins.pop_front();
      }
      que.pop_front();

    } else if (cmd == "front") {
      if (que.empty()) {
        std::cout << "error\n";
        continue;
      }
      std::cout << que.front() << '\n';

    } else if (cmd == "size") {
      std::cout << que.size() << '\n';

    } else if (cmd == "clear") {
      que.clear();
      mins.clear();
      std::cout << "ok\n";
    }

    else if (cmd == "min") {
      if (mins.empty()) {
        std::cout << "error\n";
        continue;
      }
      std::cout << mins.front() << '\n';
    }
  }

  return 0;
}