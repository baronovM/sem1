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


class LogFunctor {
 public:
  explicit LogFunctor(size_t size) : lg_(size) {
    lg_[1] = 0;
    for (size_t i = 2; i < size + 1; ++i) {
      lg_[i] = lg_[i - 1];
      if ((i & (i - 1)) == 0) {
        ++lg_[i];
      }
    }
  }

  size_t operator()(size_t number) const {
    return lg_[number];
  }
 private:
  std::vector<size_t> lg_;
};


class SparseTableSecondOrd {
 public:
  SparseTableSecondOrd(const std::vector<int>& array)
      : size_(array.size()), log_(size_), sparse_(log_(size_) + 1, std::vector<Ord>(size_)) {
    for (size_t i = 0; i < size_; ++i) {
      sparse_[0][i].ford = &array[i];
      sparse_[0][i].sord = &kMaxVal_;
    }

    for (size_t k = 0; k < log_(size_); ++k) {
      for (size_t i = 0; i < size_; ++i) {
        size_t nx = std::min(size_ - 1, i + (1 << k));
        sparse_[k + 1][i] = Merge(sparse_[k][i], sparse_[k][nx]);
      }
    }
  }

  int Get(size_t left, size_t right) const {
    size_t lglr = log_(right - left + 1);
    const Ord& first = sparse_[lglr][left];
    const Ord& second = sparse_[lglr][right + 1 - (1 << lglr)];
    return *Merge(first, second).sord;
  }

 private:
  const size_t size_;
  const LogFunctor log_;
  std::vector<std::vector<Ord>> sparse_;
  static const int kMaxVal_ = 1000000001;
};

int main() {
  int sz;
  int mreqs;
  std::cin >> sz >> mreqs;

  std::vector<int> arr(sz);
  for (int i = 0; i < sz; ++i) {
    std::cin >> arr[i];
  }

  SparseTableSecondOrd table(arr);

  while (mreqs-- > 0) {
    int left;
    int right;
    std::cin >> left >> right;
    --left;
    --right;
    std::cout << table.Get(left, right) << '\n';
  }
}