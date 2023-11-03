#include <iostream>
#include <stack>
#include <string>

#define magic 1000000000

class Hat {
 private:
  std::stack<std::pair<int, int>> iq1_;
  std::stack<std::pair<int, int>> iq2_;

 public:
  void Enqueue(int n) {
    int min = n;
    if (!iq1_.empty() && iq1_.top().second < n) {
      min = iq1_.top().second;
    }
    iq1_.push(std::make_pair(n, min));
    std::cout << "ok" << std::endl;
  }
  void Decueue() {
    bool flag = true;
    if (iq2_.empty()) {
      if (iq1_.empty()) {
        std::cout << "error" << std::endl;
        flag = false;
      } else {
        while (!iq1_.empty()) {
          int min = iq1_.top().first;
          if (!iq2_.empty() && iq1_.top().first > iq2_.top().second) {
            min = iq2_.top().second;
          }
          iq2_.push(std::make_pair(iq1_.top().first, min));
          iq1_.pop();
        }
      }
    }
    if (flag) {
      std::cout << iq2_.top().first << std::endl;
      iq2_.pop();
    }
  }
  void Front() {
    bool flag = true;
    if (iq2_.empty()) {
      if (iq1_.empty()) {
        std::cout << "error" << std::endl;
        flag = false;
      } else {
        while (!iq1_.empty()) {
          int min = iq1_.top().first;
          if (!iq2_.empty() && iq1_.top().first > iq2_.top().second) {
            min = iq2_.top().second;
          }
          iq2_.push(std::make_pair(iq1_.top().first, min));
          iq1_.pop();
        }
      }
    }
    if (flag) {
      std::cout << iq2_.top().first << std::endl;
    }
  }
  void Size() { std::cout << iq1_.size() + iq2_.size() << std::endl; }
  void Clear() {
    iq1_ = {};
    iq2_ = {};
    std::cout << "ok" << std::endl;
  }
  void Min() {
    if (iq1_.empty()) {
      if (iq2_.empty()) {
        std::cout << "error" << std::endl;
      } else {
        std::cout << iq2_.top().second << std::endl;
      }
    } else if (iq2_.empty()) {
      std::cout << iq1_.top().second << std::endl;
    } else {
      std::cout << iq1_.top().second *
                           int(iq1_.top().second < iq2_.top().second) +
                       iq2_.top().second *
                           int(iq1_.top().second >= iq2_.top().second)
                << std::endl;
    }
  }
};

int main() {
  int num;
  std::cin >> num;
  Hat hat;
  for (int i = 0; i <= num; ++i) {
    std::string input;
    std::getline(std::cin, input);
    if (input[0] == 'e') {
      std::string index;
      for (int j = (1 << 3); j < int(input.size()); ++j) {
        index += input[j];
      }
      hat.Enqueue(std::stoi(index));
    }
    if (input[0] == 'f') {
      hat.Front();
    }
    if (input[0] == 's') {
      hat.Size();
    }
    if (input[0] == 'd') {
      hat.Decueue();
    }
    if (input[0] == 'm') {
      hat.Min();
    }
    if (input[0] == 'c') {
      hat.Clear();
    }
  }
}