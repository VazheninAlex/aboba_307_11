#include <algorithm>
#include <iostream>
#include <string>

#define magic 2000000000

struct Node {
 public:
  int value;
  int depth;
  int dif;
  Node* left_son;
  Node* right_son;
  Node* parent;

  Node(int val, int dep, int di, Node* left, Node* right, Node* par)
      : value(val),
        depth(dep),
        dif(di),
        left_son(left),
        right_son(right),
        parent(par) {}
};

void Update(Node* temp) {
  if (temp->left_son == nullptr && temp->right_son == nullptr) {
    temp->depth = 1;
    temp->dif = 0;
  } else if (temp->left_son == nullptr) {
    temp->depth = temp->right_son->depth + 1;
    temp->dif = -temp->right_son->depth;
  } else if (temp->right_son == nullptr) {
    temp->depth = temp->left_son->depth + 1;
    temp->dif = temp->left_son->depth;
  } else {
    temp->depth = std::max(temp->left_son->depth, temp->right_son->depth) + 1;
    temp->dif = temp->left_son->depth - temp->right_son->depth;
  }
}

void RotateRight(Node* left, Node* right) {
  if (right->parent != nullptr) {
    if (right->parent->right_son == right) {
      right->parent->right_son = left;
    } else {
      right->parent->left_son = left;
    }
  }
  if (left->right_son != nullptr) {
    left->right_son->parent = right;
  }
  right->left_son = left->right_son;
  left->right_son = right;
  left->parent = right->parent;
  right->parent = left;
  Update(right);
  Update(left);
}

void RotateLeft(Node* left, Node* right) {
  if (left->parent != nullptr) {
    if (left->parent->right_son == left) {
      left->parent->right_son = right;
    } else {
      left->parent->left_son = right;
    }
  }
  if (right->left_son != nullptr) {
    right->left_son->parent = left;
  }
  left->right_son = right->left_son;
  right->left_son = left;
  right->parent = left->parent;
  left->parent = right;
  Update(left);
  Update(right);
}

int Find(Node* root, int num, int ans) {
  if (num == root->value) {
    return num;
  }
  if (num > root->value) {
    if (root->right_son == nullptr) {
      if (ans == magic) {
        return -1;
      }
      return ans;
    }
    return Find(root->right_son, num, ans);
  }
  if (num < root->value) {
    ans = std::min(ans, root->value);
    if (root->left_son == nullptr) {
      return ans;
    }
    return Find(root->left_son, num, ans);
  }
  return -1;
}

Node* Stabilization(Node* temp) {
  if (temp->dif == -2) {
    if (temp->right_son->dif == 0 || temp->right_son->dif == -1) {
      RotateLeft(temp, temp->right_son);
      Node* tmp = temp->parent;
      return tmp;
    }
    if (temp->right_son->dif == 1) {
      RotateRight(temp->right_son->left_son, temp->right_son);
      RotateLeft(temp, temp->right_son);
      Node* tmp = temp->parent;
      return tmp;
    }
  }
  if (temp->dif == 2) {
    if (temp->left_son->dif == 0 || temp->left_son->dif == 1) {
      RotateRight(temp->left_son, temp);
      Node* tmp = temp->parent;
      return tmp;
    }
    if (temp->left_son->dif == -1) {
      RotateLeft(temp->left_son, temp->left_son->right_son);
      RotateRight(temp->left_son, temp);
      Node* tmp = temp->parent;
      return tmp;
    }
  }
  return temp;
}

Node* Check(Node* root) {
  Node* tmp = root;
  while (tmp->parent != nullptr) {
    tmp = tmp->parent;
  }
  return tmp;
}

Node* Insert(Node* root, int num) {
  if (root == nullptr) {
    Node* temp = new Node(num, 1, 0, nullptr, nullptr, nullptr);
    return temp;
  }
  if (num == root->value) {
    return Check(root);
  }
  if (num > root->value) {
    if (root->right_son == nullptr) {
      if (num == root->value) {
        return Check(root);
      }
      Node* temp = new Node(num, 1, 0, nullptr, nullptr, root);
      root->right_son = temp;
      Node* tmp = temp;
      while (tmp->parent != nullptr) {
        tmp = tmp->parent;
        Update(tmp);
        tmp = Stabilization(tmp);
      }
      return tmp;
    }
    return Insert(root->right_son, num);
  }
  if (num < root->value) {
    if (root->left_son == nullptr) {
      if (num == root->value) {
        return Check(root);
      }
      Node* temp = new Node(num, 1, 0, nullptr, nullptr, root);
      root->left_son = temp;
      Node* tmp = temp;
      while (tmp->parent != nullptr) {
        tmp = tmp->parent;
        Update(tmp);
        tmp = Stabilization(tmp);
      }
      return tmp;
    }
    return Insert(root->left_son, num);
  }
  return root;
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
  std::cout.tie(0);
  int kum;
  std::cin >> kum;
  std::string input;
  Node* root = nullptr;
  bool flag = true;
  int val;
  std::string xxx;
  for (int i = 0; i <= kum; ++i) {
    xxx = "";
    getline(std::cin, input);
    if (input[0] == '+') {
      if (flag) {
        for (size_t j = 2; j < input.size(); ++j) {
          xxx += input[j];
        }
        root = Insert(root, std::stoi(xxx));
      } else {
        for (size_t j = 2; j < input.size(); ++j) {
          xxx += input[j];
        }
        root = Insert(root, ((std::stoi(xxx) + val) % (magic / 2)));
        flag = true;
      }
    }
    if (input[0] == '?') {
      for (size_t j = 2; j < input.size(); ++j) {
        xxx += input[j];
      }
      val = Find(root, std::stoi(xxx), magic);
      std::cout << val << "\n";
      flag = false;
    }
  }
  Clear(root);
  return 0;
}