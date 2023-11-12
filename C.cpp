#include <deque>
#include <iostream>
#include <string>

void Minus(std::deque<int>& start, std::deque<int>& finish) {
  std::cout << start.front() << "\n";
  start.pop_front();
  if (finish.size() > start.size()) {
    start.push_back(finish.front());
    finish.pop_front();
  }
}

void Plus(std::string& index, std::deque<int>& finish) {
  finish.push_back(std::stoi(index));
}

void Mult(std::string& index, std::deque<int>& finish) {
  finish.push_front(std::stoi(index));
}

void Check(std::deque<int>& start, std::deque<int>& finish) {
  start.push_back(finish.front());
  finish.pop_front();
}

int main() {
  std::deque<int> start;
  std::deque<int> finish;
  int num;
  std::cin >> num;
  for (int i = 0; i <= num; ++i) {
    std::string input;
    std::getline(std::cin, input);
    if (input[0] == '-') {
      Minus(start, finish);
      continue;
    }
    std::string index;
    for (int j = 2; j < input.size(); ++j) {
      index += input[j];
    }
    if (input[0] == '+') {
      Plus(index, finish);
    }
    if (input[0] == '*') {
      Mult(index, finish);
    }
    if (finish.size() > start.size()) {
      Check(start, finish);
    }
  }
}