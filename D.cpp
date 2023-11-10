#include <iostream>
#include <stack>
#include <string>

class Hat {
 public:
  void Enqueue(int n) {
    int min = n;
    if (!iq_front_.empty() && iq_front_.top().second < n) {
      min = iq_front_.top().second;
    }
    iq_front_.push(std::make_pair(n, min));
    std::cout << "ok" << std::endl;
  }
  void Dequeue() {
    bool flag = true;
    if (iq_back_.empty()) {
      if (iq_front_.empty()) {
        std::cout << "error" << std::endl;
        flag = false;
      } else {
        while (!iq_front_.empty()) {
          int min = iq_front_.top().first;
          if (!iq_back_.empty() && iq_front_.top().first > iq_back_.top().second) {
            min = iq_back_.top().second;
          }
          iq_back_.push(std::make_pair(iq_front_.top().first, min));
          iq_front_.pop();
        }
      }
    }
    if (flag) {
      std::cout << iq_back_.top().first << std::endl;
      iq_back_.pop();
    }
  }
  void Front() {
    bool flag = true;
    if (iq_back_.empty()) {
      if (iq_front_.empty()) {
        std::cout << "error" << std::endl;
        flag = false;
      } else {
        while (!iq_front_.empty()) {
          int min = iq_front_.top().first;
          if (!iq_back_.empty() && iq_front_.top().first > iq_back_.top().second) {
            min = iq_back_.top().second;
          }
          iq_back_.push(std::make_pair(iq_front_.top().first, min));
          iq_front_.pop();
        }
      }
    }
    if (flag) {
      std::cout << iq_back_.top().first << std::endl;
    }
  }
  void Size() { std::cout << iq_front_.size() + iq_back_.size() << std::endl; }
  void Clear() {
    iq_front_ = {};
    iq_back_ = {};
    std::cout << "ok" << std::endl;
  }
  void Min() {
    if (iq_front_.empty()) {
      if (iq_back_.empty()) {
        std::cout << "error" << std::endl;
      } else {
        std::cout << iq_back_.top().second << std::endl;
      }
    } else if (iq_back_.empty()) {
      std::cout << iq_front_.top().second << std::endl;
    } else {
      std::cout << iq_front_.top().second *
                           int(iq_front_.top().second < iq_back_.top().second) +
                       iq_back_.top().second *
                           int(iq_front_.top().second >= iq_back_.top().second)
                << std::endl;
    }
  }
  
 private:
  std::stack<std::pair<int, int>> iq_front_;
  std::stack<std::pair<int, int>> iq_back_;
};

int main() {
  int num;
  std::cin >> num;
  Hat hat;
  for (int i = 0; i <= num; ++i) {
    std::string input;
    std::getline(std::cin, input);
    if (input.find("enqueue") == 0) {
      std::string index;
      for (int j = (1 << 3); j < int(input.size()); ++j) {
        index += input[j];
      }
      hat.Enqueue(std::stoi(index));
    }
    if (input == "front") {
      hat.Front();
    }
    if (input == "size") {
      hat.Size();
    }
    if (input == "decueue") {
      hat.Dequeue();
    }
    if (input == "min") {
      hat.Min();
    }
    if (input == "clear") {
      hat.Clear();
    }
  }
}