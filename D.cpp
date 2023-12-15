#include <iostream>
#include <random>
#include <string>

#define magic 2000000000
#define magic2 100001

struct Node {
 public:
  long long key;
  long long value;
  long long degree;
  Node* left_son;
  Node* right_son;

  Node(long long ke, long long val, long long deg, Node* left, Node* right)
      : key(ke), value(val), degree(deg), left_son(left), right_son(right) {}
};

bool Exists(Node* root, long long val) {
  if (root == nullptr) {
    return false;
  }
  if (root->key == val) {
    return true;
  }
  if (root->key < val) {
    return Exists(root->right_son, val);
  }
  if (root->key > val) {
    return Exists(root->left_son, val);
  }
  return false;
}

void Update(Node* left) {
  if (left == nullptr) {
    return;
  }
  if (left->left_son == nullptr) {
    if (left->right_son == nullptr) {
      left->degree = 0;
      return;
    }
    left->degree = left->right_son->degree + 1;
    return;
  }
  if (left->right_son == nullptr) {
    left->degree = left->left_son->degree + 1;
    return;
  }
  left->degree = left->left_son->degree + left->right_son->degree + 2;
}

void Merge(Node* left, Node* right, Node*& ans) {
  if (left == nullptr) {
    ans = right;
  } else if (right == nullptr) {
    ans = left;
  } else if (left->value <= right->value) {
    Merge(left->right_son, right, left->right_son);
    ans = left;
    Update(left);
  } else {
    Merge(left, right->left_son, right->left_son);
    ans = right;
    Update(right);
  }
}

std::pair<Node*, Node*> Split(Node* root, long long keyz) {
  if (root == nullptr) {
    return std::make_pair(nullptr, nullptr);
  }
  if (root->key <= keyz) {
    std::pair<Node*, Node*> res = Split(root->right_son, keyz);
    root->right_son = res.first;
    Update(root);
    Update(res.second);
    return std::make_pair(root, res.second);
  }
  if (root->key > keyz) {
    std::pair<Node*, Node*> res = Split(root->left_son, keyz);
    root->left_son = res.second;
    Update(root);
    Update(res.first);
    return std::make_pair(res.first, root);
  }
  return std::make_pair(nullptr, nullptr);
}

Node* Insert(Node* root, long long in) {
  if (Exists(root, in)) {
    return root;
  }
  if (root == nullptr) {
    std::random_device rd;
    std::mt19937 gen(rd());
    Node* temp = new Node(in, gen() % magic2, 0, nullptr, nullptr);
    return temp;
  }
  std::pair<Node*, Node*> res = Split(root, in);
  std::random_device rd;
  std::mt19937 gen(rd());
  Node* temp = new Node(in, gen() % magic2, 0, nullptr, nullptr);
  Node* tmp1;
  Node* tmp2;
  Merge(temp, res.second, tmp1);
  Merge(res.first, tmp1, tmp2);
  return tmp2;
}

Node* Delete(Node* root, long long out) {
  if (!Exists(root, out)) {
    return root;
  }
  std::pair<Node*, Node*> res1 = Split(root, out);
  std::pair<Node*, Node*> res2 = Split(res1.first, out - 1);
  delete res2.second;
  Node* tmp;
  Merge(res2.first, res1.second, tmp);
  return tmp;
}

long long Next(Node* root, long long qw) {
  std::pair<Node*, Node*> res = Split(root, qw);
  if (res.second == nullptr) {
    return magic;
  }
  Node* temp = res.second;
  while (temp->left_son != nullptr) {
    temp = temp->left_son;
  }
  Node* ans;
  Merge(res.first, res.second, ans);
  return temp->key;
}

long long Prev(Node* root, long long qw) {
  std::pair<Node*, Node*> res = Split(root, qw - 1);
  if (res.first == nullptr) {
    return magic;
  }
  Node* temp = res.first;
  while (temp->right_son != nullptr) {
    temp = temp->right_son;
  }
  Node* ans;
  Merge(res.first, res.second, ans);
  return temp->key;
}

long long Kth(Node* root, long long qw) {
  if (root == nullptr) {
    return magic;
  }
  if (qw > root->degree) {
    return magic;
  }
  if (root->left_son == nullptr) {
    if (qw == 0) {
      return root->key;
    }
    return Kth(root->right_son, qw - 1);
  }
  if (qw == root->left_son->degree) {
    return root->left_son->key;
  }
  if (qw == (root->left_son->degree + 1)) {
    return root->key;
  }
  if (qw == (root->left_son->degree + 2)) {
    return root->right_son->key;
  }
  if (qw < root->left_son->degree) {
    return Kth(root->left_son, qw);
  }
  if (qw > (root->left_son->degree + 2)) {
    return Kth(root->right_son, qw - 2 - root->left_son->degree);
  }
  return magic;
}

void Ans(long long ans) {
  if (ans == magic) {
    std::cout << "none\n";
  } else {
    std::cout << ans << "\n";
  }
}

void Clear(Node* root) {
  if (root == nullptr) {
    return;
  }
  Clear(root->left_son);
  Clear(root->right_son);
  delete root;
}

int main() {
  std::cin.tie(0);
  std::string command;
  std::string val;
  Node* root = nullptr;
  while (std::cin >> command >> val) {
    if (command == "insert") {
      root = Insert(root, std::stoi(val));
    }
    if (command == "exists") {
      if (Exists(root, std::stoi(val))) {
        std::cout << "true\n";
      } else {
        std::cout << "false\n";
      }
    }
    if (command == "delete") {
      root = Delete(root, std::stoi(val));
    }
    if (command == "next") {
      long long ans = Next(root, std::stoi(val));
      Ans(ans);
    }
    if (command == "prev") {
      long long ans = Prev(root, std::stoi(val));
      Ans(ans);
    }
    if (command == "kth") {
      long long ans = Kth(root, std::stoi(val));
      Ans(ans);
    }
  }
  Clear(root);
}