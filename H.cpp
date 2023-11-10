#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

const int magic = 30;

class Heap {
 public:
  std::pair<long long, long long> GetMin() { return values_[0]; }
  long long Size() { return values_.size(); }
  void Clear() {
    values_ = {};
    decrease_ = {};
  }
  void Insert(long long val, long long index) {
    values_.push_back(std::make_pair(val, index));
    decrease_.insert({index, values_.size() - 1});
    SiftUp(values_.size() - 1);
  }
  void ExtractMin() {
    decrease_.erase(values_[0].second);
    values_[0] = values_.back();
    decrease_[values_[0].second] = 0;
    values_.pop_back();
    SiftDown(0);
  }
  void DecreaseKey(long long index, long long delta) {
    values_[decrease_[index]].first -= delta;
    SiftUp(decrease_[index]);
  }
  void Swap(long long first, long long second) {
    auto temp = values_[first];
    values_[first] = values_[second];
    values_[second] = temp;
    decrease_[values_[second].second] = second;
    decrease_[values_[first].second] = first;
  }

  void SiftUp(long long num) {
    if (num == 0) {
      return;
    }
    if (values_[num].first < values_[((num + 1) / 2) - 1].first) {
      Swap(num, ((num + 1) / 2) - 1);
    } else {
      return;
    }
    SiftUp(((num + 1) / 2) - 1);
  }
  void SiftDown(long long num) {
    if (num >= static_cast<long long>(values_.size() / 2)) {
      return;
    }
    if ((values_[num].first > values_[2 * num + 1].first) ||
        (values_[num].first > values_[2 * num + 2].first)) {
      if (values_[2 * num + 1].first > values_[2 * num + 2].first) {
        Swap(num, 2 * num + 2);
        SiftDown(2 * num + 2);
      } else {
        Swap(num, 2 * num + 1);
        SiftDown(2 * num + 1);
      }
    } else {
      return;
    }
  }
  
 private:
  std::vector<std::pair<long long, long long>> values_;
  std::unordered_map<long long, long long> decrease_;
};

class DoubleHeap {
 public:
  void Insert(long long val, long long index) {
    min_.Insert(val, index);
    max_.Insert(val * (-1), index);
    std::cout << "ok"
              << "\n";
  }
  void GetMin() {
    if (min_.Size() == 0) {
      std::cout << "error"
                << "\n";
      return;
    }
    std::cout << min_.GetMin().first << "\n";
  }
  void GetMax() {
    if (min_.Size() == 0) {
      std::cout << "error"
                << "\n";
      return;
    }
    std::cout << (-1) * max_.GetMin().first << "\n";
  }
  void Clear() {
    max_.Clear();
    min_.Clear();
    std::cout << "ok"
              << "\n";
  }
  void Size() { std::cout << max_.Size() << "\n"; }
  void ExtractMin() {
    if (min_.Size() == 0) {
      std::cout << "error"
                << "\n";
      return;
    }
    auto min = min_.GetMin();
    std::cout << min.first << "\n";
    min_.ExtractMin();
    max_.DecreaseKey(min.second, (1 << magic));
    max_.ExtractMin();
  }
  void ExtractMax() {
    if (min_.Size() == 0) {
      std::cout << "error"
                << "\n";
      return;
    }
    auto max = max_.GetMin();
    std::cout << (-1) * max.first << "\n";
    max_.ExtractMin();
    min_.DecreaseKey(max.second, (1 << magic));
    min_.ExtractMin();
  }
  
 private:
  Heap max_;
  Heap min_;
};

int main() {
  std::cin.tie(0);
  std::cout.tie(0);
  long long qual;
  std::cin >> qual;
  std::string input;
  DoubleHeap heap;
  for (long long i = 0; i <= qual; ++i) {
    std::getline(std::cin, input);
    if (input.find("insert") == 0) {
      std::string index;
      for (long long j = 7; j < static_cast<long long>(input.size());
           ++j) {
        index += input[j];
      }
      heap.Insert(std::stoi(index), i);
    }
    if (input == "size") {
      heap.Size();
    }
    if (input == "clear") {
      heap.Clear();
    }
    if (input == "get_max") {
      heap.GetMax();
    }
    if (input == "get_min") {
      heap.GetMin();
    }
    if (input == "extract_max") {
      heap.ExtractMax();
    }
    if (input == "extract_min") {
      heap.ExtractMin();
    }
  }
}