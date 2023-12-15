#include <algorithm>
#include <iostream>
#include <string>

#define magic 2000000000

struct Node {
 public:
  std::string value;
  std::string key;
  int depth;
  int dif;
  Node* left_son;
  Node* right_son;
  Node* parent;

  Node(std::string val, std::string ke, int dep, int di, Node* left,
       Node* right, Node* par)
      : value(val),
        key(ke),
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

std::string Find(Node* root, std::string num) {
  if (root == nullptr) {
    return "Errrrrror";
  }
  if (num == root->value) {
    return root->key;
  }
  if (num > root->value) {
    return Find(root->right_son, num);
  }
  if (num < root->value) {
    return Find(root->left_son, num);
  }
  return "Errrrrror";
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

Node* Insert(Node* root, std::pair<std::string, std::string> num) {
  if (root == nullptr) {
    Node* temp =
        new Node(num.first, num.second, 1, 0, nullptr, nullptr, nullptr);
    return temp;
  }
  if (num.first > root->value) {
    if (root->right_son == nullptr) {
      Node* temp =
          new Node(num.first, num.second, 1, 0, nullptr, nullptr, root);
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
  if (num.first < root->value) {
    if (root->left_son == nullptr) {
      Node* temp =
          new Node(num.first, num.second, 1, 0, nullptr, nullptr, root);
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
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int kum;
  std::cin >> kum;
  std::string input1;
  std::string input2;
  Node* root1 = nullptr;
  Node* root2 = nullptr;
  for (int i = 0; i < kum; ++i) {
    std::cin >> input1 >> input2;
    root1 = Insert(root1, std::make_pair(input1, input2));
    root2 = Insert(root2, std::make_pair(input2, input1));
  }
  int qum;
  std::cin >> qum;
  for (int i = 0; i < qum; ++i) {
    std::cin >> input1;
    if (Find(root1, input1) == "Errrrrror") {
      std::cout << Find(root2, input1) << "\n";
    } else {
      std::cout << Find(root1, input1) << "\n";
    }
  }
  Clear(root1);
  Clear(root2);
  return 0;
}