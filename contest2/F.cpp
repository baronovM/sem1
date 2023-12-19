#include <iostream>
#include <vector>

class BinaryHeap {
public:
  void ResIds(int number) { index_by_id_.resize(number); }

  void Insert(long long value, int id) {
    data_.push_back(value);
    id_by_index_.push_back(id);
    index_by_id_[id] = size_++;
    SiftUp(size_ - 1);
  }

  long long GetMin() { return data_[0]; }

  void ExtractMin() {
    SwapElements(0, --size_);
    data_.pop_back();
    id_by_index_.pop_back();
    SiftDown(0);
  }

  void DecreaseKey(int id, long long delta) {
    data_[index_by_id_[id]] -= delta;
    SiftUp(index_by_id_[id]);
  }

 private:
  void SwapElements(int ind1, int ind2) {
    std::swap(data_[ind1], data_[ind2]);
    std::swap(index_by_id_[id_by_index_[ind1]],
              index_by_id_[id_by_index_[ind2]]);
    std::swap(id_by_index_[ind1], id_by_index_[ind2]);
  }

  void SiftUp(int index) {
    if (index == 0) {
      return;
    }
    if (data_[index] < data_[index / 2]) {
      SwapElements(index, index / 2);
      SiftUp(index / 2);
    }
  }

  void SiftDown(int index) {
    if (index * 2 < size_ && data_[index] > data_[index * 2]) {
      SwapElements(index, index * 2);
      SiftDown(index * 2);
    }
    if (index * 2 + 1 < size_ && data_[index] > data_[index * 2 + 1]) {
      SwapElements(index, index * 2 + 1);
      SiftDown(index * 2 + 1);
    }
  }

  int size_ = 0;
  std::vector<long long> data_;
  std::vector<int> id_by_index_;
  std::vector<int> index_by_id_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  BinaryHeap heap;

  int number_of_requests;
  std::cin >> number_of_requests;
  std::string command;
  heap.ResIds(number_of_requests);

  for (int i = 0; i < number_of_requests; ++i) {
    std::cin >> command;
    if (command == "insert") {
      long long x;
      std::cin >> x;
      heap.Insert(x, i);
    } else if (command == "getMin") {
      std::cout << heap.GetMin() << '\n';
    } else if (command == "extractMin") {
      heap.ExtractMin();
    } else if (command == "decreaseKey") {
      int id;
      long long delta;
      std::cin >> id >> delta;
      heap.DecreaseKey(id - 1, delta);
    }
  }
}