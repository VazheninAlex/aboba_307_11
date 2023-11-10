#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Heap {
 public:
  long long GetMin() { return values_[0].first; }
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

int main() {
  std::cin.tie(0);
  std::cout.tie(0);
  long long qual;
  std::cin >> qual;
  std::string input;
  Heap heap;
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
    if (input.find("decreaseKey") == 0) {
      std::string index;
      std::string delta;
      long long jum;
      for (jum = 12;
           jum < static_cast<long long>(input.find(" ", (1 << 4) - 3)); ++jum) {
        index += input[jum];
      }
      for (jum++; jum < static_cast<long long>(input.size()); ++jum) {
        delta += input[jum];
      }
      heap.DecreaseKey(std::stoi(index), std::stoi(delta));
    }
    if (input == "getMin") {
      std::cout << heap.GetMin() << "\n";
    }
    if (input == "extractMin") {
      heap.ExtractMin();
    }
  }
}