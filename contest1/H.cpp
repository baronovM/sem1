#include <iostream>
#include <random>
#include <vector>

std::mt19937 mt(time(nullptr));

void QuickSort(std::vector<int>::iterator begin,
               std::vector<int>::iterator end) {
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

  if (less != 0) {
    QuickSort(begin, begin + less);
  }
  if (less + equal != end - begin) {
    QuickSort(begin + less + equal, end);
  }
}

int main() {
  int size;
  std::cin >> size;
  std::vector<int> arr(size);
  for (int i = 0; i < size; ++i) {
    std::cin >> arr[i];
  }
  QuickSort(arr.begin(), arr.end());
  for (int i = 0; i < size; ++i) {
    std::cout << arr[i] << ' ';
  }

  return 0;
}