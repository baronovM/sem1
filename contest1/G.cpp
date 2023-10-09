#include <iostream>
#include <vector>

const int kBitInByte = 8;
const int kByte = 256;
const int kByteMask = 0b11111111;

void LSDSort(std::vector<long long>& arr) {
  std::vector<std::vector<long long>> bins(kByte);
  for (int iter_num = 0; iter_num < int(sizeof(long long)); ++iter_num) {
    for (long long x : arr) {
      bins[(x >> (iter_num * kBitInByte)) & kByteMask].push_back(x);
    }
    int ind = 0;
    for (int j = 0; j < kByte; ++j) {
      for (long long x : bins[j]) {
        arr[ind++] = x;
      }
      bins[j].clear();
    }
  }
}

int main() {
  int size;
  std::cin >> size;
  std::vector<long long> arr(size);
  for (int i = 0; i < size; ++i) {
    std::cin >> arr[i];
  }
  LSDSort(arr);
  for (int i = 0; i < size; ++i) {
    std::cout << arr[i] << '\n';
  }

  return 0;
}