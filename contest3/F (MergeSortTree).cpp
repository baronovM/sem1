#include <iostream>
#include <vector>

int LowerBound(const std::vector<int>& arr, int val) {
  int left = -1;
  int right = arr.size();

  while (right - left > 1) {
    int mid = (left + right) / 2;

    if (arr[mid] >= val) {
      right = mid;
    } else {
      left = mid;
    }
  }
  return right;
}

int UpperBound(const std::vector<int>& arr, int val) {
  int left = -1;
  int right = arr.size();

  while (right - left > 1) {
    int mid = (left + right) / 2;

    if (arr[mid] > val) {
      right = mid;
    } else {
      left = mid;
    }
  }
  return left;
}

void Merge(std::vector<int>& first_arr, std::vector<int>& second_arr,
           std::vector<int>& res_arr) {
  int a_size = first_arr.size();
  int b_size = second_arr.size();
  int index_a = 0;
  int index_b = 0;
  while (index_a < a_size || index_b < b_size) {
    if (index_b == b_size ||
        (index_a < a_size && first_arr[index_a] <= second_arr[index_b])) {
      res_arr[index_a + index_b] = first_arr[index_a];
      ++index_a;
    } else {
      res_arr[index_a + index_b] = second_arr[index_b];
      ++index_b;
    }
  }
}

class Node {
 public:
  Node(int tl, int tr) : tl_(tl), tm_((tl + tr) / 2), tr_(tr) {}

  ~Node() {
    delete left_son_;
    delete right_son_;
  }

  void Build(const std::vector<int>& arr) {
    if (tl_ == tr_) {
      seg_ = {arr[tl_]};
      return;
    }

    (left_son_ = new Node(tl_, tm_))->Build(arr);
    (right_son_ = new Node(tm_ + 1, tr_))->Build(arr);

    seg_.resize(left_son_->seg_.size() + right_son_->seg_.size());
    Merge(left_son_->seg_, right_son_->seg_, seg_);
  }

  int CalcAns(int seg_start, int seg_end, int val_from, int val_to) {
    if (seg_start == tl_ && seg_end == tr_) {
      return UpperBound(seg_, val_to) - LowerBound(seg_, val_from) + 1;
    }
    int ans = 0;
    if (seg_start <= tm_) {
      ans += left_son_->CalcAns(seg_start, std::min(seg_end, tm_), val_from,
                                val_to);
    }
    if (seg_end >= tm_ + 1) {
      ans += right_son_->CalcAns(std::max(seg_start, tm_ + 1), seg_end,
                                 val_from, val_to);
    }
    return ans;
  }

 private:
  std::vector<int> seg_;
  int tl_;
  int tm_;
  int tr_;
  Node* left_son_ = nullptr;
  Node* right_son_ = nullptr;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int arr_size;
  std::cin >> arr_size;
  int reqs;
  std::cin >> reqs;
  std::vector<int> arr(arr_size);
  for (int i = 0; i < arr_size; ++i) {
    std::cin >> arr[i];
  }
  Node* tree = new Node(0, arr_size - 1);
  tree->Build(arr);
  int seg_start;
  int seg_end;
  int val_from;
  int val_to;
  while (reqs-- > 0) {
    std::cin >> seg_start >> seg_end >> val_from >> val_to;
    --seg_start;
    --seg_end;
    std::cout << tree->CalcAns(seg_start, seg_end, val_from, val_to) << '\n';
  }
  delete tree;
}