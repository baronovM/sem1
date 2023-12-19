#include <iostream>
#include <vector>

struct Ord {
  const int* ford;
  const int* sord;
};

Ord Merge(const Ord& left, const Ord& right) {
  Ord res;
  if (*left.ford < *right.ford) {
    res.ford = left.ford;
    res.sord = *left.sord < *right.ford ? left.sord : right.ford;
  } else if (*left.ford > *right.ford) {
    res.ford = right.ford;
    res.sord = *right.sord < *left.ford ? right.sord : left.ford;
  } else {
    res.ford = left.ford;
    if (left.ford != right.ford) {
      res.sord = right.ford;
    } else {
      res.sord = *left.sord < *right.sord ? left.sord : right.sord;
    }
  }
  return res;
}

int main() {
  int sz;
  int mreqs;
  std::cin >> sz >> mreqs;

  std::vector<int> lg(sz + 1);
  lg[1] = 0;
  for (int i = 2; i < sz + 1; ++i) {
    lg[i] = lg[i - 1];
    if ((i & (i - 1)) == 0) {
      ++lg[i];
    }
  }

  std::vector<int> arr(sz);
  for (int i = 0; i < sz; ++i) {
    std::cin >> arr[i];
  }
  std::vector<std::vector<Ord>> sparse(lg[sz] + 1, std::vector<Ord>(sz));
  const int kMaxVal = 1000000001;
  for (int i = 0; i < sz; ++i) {
    sparse[0][i].ford = &arr[i];
    sparse[0][i].sord = &kMaxVal;
  }

  for (int k = 0; k < lg[sz]; ++k) {
    for (int i = 0; i < sz; ++i) {
      int nx = std::min(sz - 1, i + (1 << k));
      sparse[k + 1][i] = Merge(sparse[k][i], sparse[k][nx]);
    }
  }

  while (mreqs-- > 0) {
    int left;
    int right;
    std::cin >> left >> right;
    --left;
    --right;
    int lglr = lg[right - left + 1];
    const Ord& first = sparse[lglr][left];
    const Ord& second = sparse[lglr][right + 1 - (1 << lglr)];
    std::cout << *Merge(first, second).sord << '\n';
  }
}