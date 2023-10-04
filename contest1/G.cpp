#include <iostream>
#include <vector>

using Ll = long long;

const int kBitInByte = 8;
const int kByte = 256;
const int kByteMask = 0b11111111;

void LsdSort(std::vector<Ll>& arr) {
  std::vector<std::vector<Ll>> bins(kByte);
  for (int iter_num = 0; iter_num < int(sizeof(Ll)); ++iter_num) {
    for (Ll x : arr) {
      bins[(x >> (iter_num * kBitInByte)) & kByteMask].push_back(x);
    }
    int ind = 0;
    for (int j = 0; j < kByte; ++j) {
      for (Ll x : bins[j]) {
        arr[ind++] = x;
      }
      bins[j].clear();
    }
  }
}

int main() {
  int size;
  std::cin >> size;
  std::vector<Ll> arr(size);
  for (int i = 0; i < size; ++i) {
    std::cin >> arr[i];
  }
  LsdSort(arr);
  for (int i = 0; i < size; ++i) {
    std::cout << arr[i] << '\n';
  }

  return 0;
}