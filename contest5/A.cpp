#include <iostream>

const long long kEmpty = -1;
const long long kDeleted = -2;
const size_t kStartM = 32;

class HashTable {
  size_t a_;
  size_t b_;
  size_t m_;
  size_t size_;
  long long* arr_;

  void Rehash() {
    long long* temparr = new long long[m_];
    std::copy(arr_, arr_ + m_, temparr);
    m_ <<= 1;
    arr_ = new long long[m_];
    for (size_t i = 0; i < (m_ >> 1); ++i) {
      if (temparr[i] != kEmpty && temparr[i] != kDeleted) {
        Insert(temparr[i]);
      }
    }
    delete[] temparr;
  }

 public:
  HashTable(size_t aa, size_t bb, size_t size = kStartM)
      : a_(aa), b_(bb), m_(size << 1), size_(0), arr_(new long long[m_]) {
    std::fill(arr_, arr_ + m_, kEmpty);
  }

  bool Exists(unsigned xx) {
    size_t hs = (a_ * xx + b_) % m_;
    for (size_t i = 0; i < m_; ++i) {
      size_t index = (hs + i) % m_;
      if (arr_[index] == kEmpty) {
        return false;
      }
      if (arr_[index] == xx) {
        return true;
      }
    }
    return false;
  }

  void Insert(unsigned xx) {
    if (Exists(xx)) {
      return;
    }
    size_t hs = (a_ * xx + b_) % m_;
    for (size_t i = 0; i < m_; ++i) {
      size_t index = (hs + i) % m_;
      if (arr_[index] == kEmpty || arr_[index] == kDeleted) {
        arr_[index] = xx;
        if (++size_ * 2 > m_) {
          Rehash();
        }
        return;
      }
    }
  }

  void Del(unsigned xx) {
    size_t hs = (a_ * xx + b_) % m_;
    for (size_t i = 0; i < m_; ++i) {
      size_t index = (hs + i) % m_;
      if (arr_[index] == kEmpty) {
        return;
      }
      if (arr_[index] == xx) {
        arr_[index] = kDeleted;
        --size_;
        return;
      }
    }
  }

  ~HashTable() { delete[] arr_; }
};

int main() {
  int num;
  std::cin >> num;

  const size_t kA = 1000000007;
  const size_t kB = 12345;

  HashTable set(kA, kB, num);

  char cmd;
  int xx;
  for (int i = 0; i < num; ++i) {
    std::cin >> cmd >> xx;
    if (cmd == '+') {
      set.Insert(xx);
    } else if (cmd == '-') {
      set.Del(xx);
    } else if (cmd == '?') {
      std::cout << (set.Exists(xx) ? "YES\n" : "NO\n");
    }
  }

  return 0;
}
