#include <deque>
#include <iostream>

int main() {
  int num;
  std::cin >> num;
  std::deque<int> first_half;
  std::deque<int> second_half;
  char req;
  int goblin;
  while (num-- > 0) {
    std::cin >> req;
    if (req == '+') {
      std::cin >> goblin;
      second_half.push_back(goblin);
    } else if (req == '*') {
      std::cin >> goblin;
      first_half.push_back(goblin);
    } else if (req == '-') {
      std::cout << first_half.front() << '\n';
      first_half.pop_front();
    }

    if (first_half.size() < second_half.size()) {
      first_half.push_back(second_half.front());
      second_half.pop_front();
    } else if (first_half.size() > second_half.size() + 1) {
      second_half.push_front(first_half.back());
      first_half.pop_back();
    }
  }

  return 0;
}