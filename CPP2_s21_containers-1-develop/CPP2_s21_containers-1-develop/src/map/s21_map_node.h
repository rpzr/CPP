#ifndef S21_MAP_NODE_H
#define S21_MAP_NODE_H

#include "s21_map.h"
namespace s21 {

template <typename Key, typename T>
struct map<Key, T>::Node {
  Node(value_type value) : value(value) {}
  void right_rotate();
  void left_rotate();
  Node* max();
  Node* min();
  Node* next();
  Node* prev();
  Node* root();
  void destruct();

  Node* left_child = nullptr;
  Node* right_child = nullptr;
  Node* parent = nullptr;
  bool color = COLOR_BLACK;
  value_type value;
};

// Метод для правого поворота узла
template <typename Key, typename T>
void map<Key, T>::Node::right_rotate() {
  if (left_child == nullptr) throw std::logic_error("No left child to rotate");
  Node* rotated = left_child;
  if (parent) {
    if (parent->left_child == this) {
      parent->left_child = rotated;
    } else {
      parent->right_child = rotated;
    }
  }
  rotated->parent = parent;
  parent = rotated;
  left_child = rotated->right_child;
  if (left_child) left_child->parent = this;
  rotated->right_child = this;
}

// Метод для левого поворота узла
template <typename Key, typename T>
void map<Key, T>::Node::left_rotate() {
  if (right_child == nullptr)
    throw std::logic_error("No right child to rotate");
  Node* rotated = right_child;
  if (parent) {
    if (parent->left_child == this) {
      parent->left_child = rotated;
    } else {
      parent->right_child = rotated;
    }
  }
  rotated->parent = parent;
  parent = rotated;
  right_child = rotated->left_child;
  if (right_child) right_child->parent = this;
  rotated->left_child = this;
}

// Метод для поиска максимального узла
template <typename Key, typename T>
typename map<Key, T>::Node* map<Key, T>::Node::max() {
  Node* ptr = this;
  while (ptr && ptr->right_child) ptr = ptr->right_child;
  return ptr;
}

// Метод для поиска минимального узла
template <typename Key, typename T>
typename map<Key, T>::Node* map<Key, T>::Node::min() {
  Node* ptr = this;
  while (ptr && ptr->left_child) ptr = ptr->left_child;
  return ptr;
}

// Метод для поиска следующего узла
template <typename Key, typename T>
typename map<Key, T>::Node* map<Key, T>::Node::next() {
  Node* ptr = this;
  if (ptr->right_child) {
    ptr = ptr->right_child->min();
  } else {
    while (ptr->parent && ptr->parent->right_child == ptr) ptr = ptr->parent;
    ptr = ptr->parent;
  }
  return (ptr == this) ? nullptr : ptr;
}

// Метод для поиска предыдущего узла
template <typename Key, typename T>
typename map<Key, T>::Node* map<Key, T>::Node::prev() {
  Node* ptr = this;
  if (ptr->left_child) {
    ptr = ptr->left_child->max();
  } else {
    while (ptr->parent && ptr->parent->left_child == ptr) ptr = ptr->parent;
    ptr = ptr->parent;
  }
  return (ptr == this) ? nullptr : ptr;
}

// Метод для поиска корня дерева
template <typename Key, typename T>
typename map<Key, T>::Node* map<Key, T>::Node::root() {
  Node* ptr = this;
  while (ptr->parent) ptr = ptr->parent;
  return ptr;
}

// Метод для рекурсивного удаления дерева
template <typename Key, typename T>
void map<Key, T>::Node::destruct() {
  if (left_child) left_child->destruct();
  if (right_child) right_child->destruct();
  delete this;
}

}  // namespace s21

#endif  // S21_MAP_NODE_H