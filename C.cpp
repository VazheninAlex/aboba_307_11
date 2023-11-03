#include <deque>
#include <iostream>
#include <string>

int main() {
  std::deque<int> start;
  std::deque<int> finish;
  int num;
  std::cin >> num;
  for (int i = 0; i <= num; ++i) {
    std::string input;
    std::getline(std::cin, input);
    if (input[0] == '-') {
      std::cout << start.front() << "\n";
      start.pop_front();
      if (finish.size() > start.size()) {
        start.push_back(finish.front());
        finish.pop_front();
      }
      continue;
    }
    std::string index;
    for (int j = 2; j < input.size(); ++j) {
      index += input[j];
    }
    if (input[0] == '+') {
      finish.push_back(std::stoi(index));
    }
    if (input[0] == '*') {
      finish.push_front(std::stoi(index));
    }
    if (finish.size() > start.size()) {
      start.push_back(finish.front());
      finish.pop_front();
    }
  }
}