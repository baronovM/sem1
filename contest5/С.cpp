#include <iostream>
#include <string>
#include <vector>

const size_t kStartCap = 500;

const std::string kEmpty = "\1";
const std::string kDeleted = "\2";

class HashTable {
 public:
  HashTable(size_t pp, size_t cap = kStartCap)
      : p_(pp), m_(cap << 1), arr_(new std::string[m_]) {
    std::fill(arr_, arr_ + m_, kEmpty);
  }

  ~HashTable() { delete[] arr_; }

  bool Exists(const std::string& str) const {
    size_t hs = hash(str);
    for (size_t i = 0; i < m_; ++i) {
      size_t index = (hs + i) % m_;
      if (arr_[index] == kEmpty) {
        return false;
      }
      if (arr_[index] != kDeleted && arr_[index] == str) {
        return true;
      }
    }
    return false;
  }

  void Insert(const std::string& str) {
    size_t hs = hash(str);
    for (size_t i = 0; i < m_; ++i) {
      size_t index = (hs + i) % m_;
      if (arr_[index] == kEmpty || arr_[index] == kDeleted) {
        arr_[index] = str;
        return;
      }
    }
  }

 private:
  size_t hash(const std::string& str) const {
    size_t hs = 0;
    for (char let : str) {
      hs *= p_;
      hs += let;
    }
    return hs % m_;
  }

  size_t p_;
  size_t m_;
  std::string* arr_;
};

const int kAlphabetSize = 26;
void HandleName(std::string& str) {
  std::vector<char> repl(kAlphabetSize, '\0');
  char first_unused = 'a';
  for (char& let : str) {
    if (repl[let - 'a'] == '\0') {
      repl[let - 'a'] = first_unused++;
    }
    let = repl[let - 'a'];
  }
}

int main() {

  int qreq;
  std::cin >> qreq;
  const size_t kP = 37;
  HashTable set(kP, qreq);
  char cmd;
  std::string name;
  while (qreq-- > 0) {
    std::cin >> cmd >> name;
    HandleName(name);
    if (cmd == '+') {
      set.Insert(name);
    } else {
      std::cout << (set.Exists(name) ? "YES\n" : "NO\n");
    }
  }

  return 0;
}
