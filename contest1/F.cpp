#include <iostream>
#include <random>
#include <vector>

std::mt19937 mt(time(nullptr));

int QuickSelect(std::vector<int>::iterator begin,
                std::vector<int>::iterator end, int k_ordstat) {
  int pivot = *(begin + mt() % (end - begin));

  // partition
  int less = 0;
  int equal = 0;
  for (auto i = begin; i != end; ++i) {
    if (*i == pivot) {
      std::swap(*i, *(begin + less + equal));
      ++equal;
    } else if (*i < pivot) {
      std::swap(*i, *(begin + less));
      if (*i == pivot) {
        std::swap(*i, *(begin + less + equal));
      }
      ++less;
    }
  }
  //

  if (k_ordstat <= less) {
    return QuickSelect(begin, begin + less, k_ordstat);
  }
  if (k_ordstat > less + equal) {
    return QuickSelect(begin + less + equal, end, k_ordstat - less - equal);
  }
  return pivot;
}

int main() {
  int sequence_size;
  std::cin >> sequence_size;
  int k_ordstat;
  std::cin >> k_ordstat;
  int first_elem;
  std::cin >> first_elem;
  int second_elem;
  std::cin >> second_elem;
  std::vector<int> arr(sequence_size);
  arr[0] = first_elem;
  arr[1] = second_elem;

  // :)
  const int kMagicNumberForFormula1 = 123;
  const int kMagicNumberForFormula2 = 45;
  const int kMagicNumberForFormula3 = 10000000;
  const int kMagicNumberForFormula4 = 4321;

  for (int i = 2; i < sequence_size; ++i) {
    arr[i] = (arr[i - 1] * kMagicNumberForFormula1 +
              arr[i - 2] * kMagicNumberForFormula2) %
             (kMagicNumberForFormula3 + kMagicNumberForFormula4);
  }

  std::cout << QuickSelect(arr.begin(), arr.end(), k_ordstat);

  return 0;
}