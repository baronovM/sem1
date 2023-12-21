#include <iostream>
#include <vector>

const size_t kStartCap = 500;

using TableCell = std::pair<long long, unsigned>;

const TableCell kEmpty = {-1, 0};
const TableCell kDeleted = {-2, 0};

class HashTable {
  size_t a_;
  size_t b_;
  size_t m_;
  size_t size_;
  TableCell* arr_;

  void Rehash() {
    TableCell* temparr = new TableCell[m_];
    std::copy(arr_, arr_ + m_, temparr);
    size_t oldm = m_;
    m_ <<= 1;
    arr_ = new TableCell[m_];
    std::fill(arr_, arr_ + m_, kEmpty);
    for (size_t i = 0; i < oldm; ++i) {
      if (temparr[i] != kEmpty && temparr[i] != kDeleted) {
        Increase(temparr[i].first, temparr[i].second);
      }
    }
    delete[] temparr;
  }

 public:
  HashTable(size_t aa, size_t bb, size_t cap = kStartCap)
      : a_(aa), b_(bb), m_(cap << 1), size_(0), arr_(new TableCell[m_]) {
    std::fill(arr_, arr_ + m_, kEmpty);
  }

  unsigned Get(unsigned xx) const {
    size_t hs = (a_ * xx + b_) % m_;
    for (size_t i = 0; i < m_; ++i) {
      size_t index = (hs + i) % m_;
      if (arr_[index] == kEmpty) {
        return 0;
      }
      if (arr_[index] != kDeleted && arr_[index].first == xx) {
        return arr_[index].second;
      }
    }
    return 0;
  }

  void Increase(unsigned xx, unsigned delta = 1) {
    size_t hs = (a_ * xx + b_) % m_;
    size_t first_gap = m_;
    for (size_t i = 0; i < m_; ++i) {
      size_t index = (hs + i) % m_;
      if (arr_[index] == kEmpty || arr_[index] == kDeleted) {
        if (first_gap == m_) {
          first_gap = i;
        }
        if (arr_[index] == kEmpty) {
          break;
        }
      } else if (arr_[index].first == xx) {
        arr_[index].second += delta;
        return;
      }
    }

    arr_[(hs + first_gap) % m_] = {xx, delta};
    if ((++size_ << 1) >= m_) {
      Rehash();
    }
  }

  void Decrease(unsigned xx) {
    size_t hs = (a_ * xx + b_) % m_;
    for (size_t i = 0; i < m_; ++i) {
      size_t index = (hs + i) % m_;
      if (arr_[index] == kEmpty) {
        return;
      }
      if (arr_[index] != kDeleted && arr_[index].first == xx) {
        if (--arr_[index].second == 0) {
          arr_[index] = kDeleted;
          --size_;
        }
        return;
      }
    }
  }

  ~HashTable() { delete[] arr_; }
};

int main() {
  unsigned num;
  std::cin >> num;

  const size_t kA = 1000000007;
  const size_t kB = 12345;

  HashTable first_collection(kA, kB);

  unsigned aa;
  while (num-- > 0) {
    std::cin >> aa;
    first_collection.Increase(aa);
  }

  std::cin >> num;

  std::vector<unsigned> ans;
  while (num-- > 0) {
    std::cin >> aa;

    if (first_collection.Get(aa) != 0) {
      first_collection.Decrease(aa);
      ans.push_back(aa);
    }
  }

  std::cout << ans.size() << '\n';
  for (unsigned an : ans) {
    std::cout << an << ' ';
  }

  return 0;
}
