#ifndef S21_MAP_H
#define S21_MAP_H

#include <stdarg.h>

#include <cstddef>
#include <iostream>
#include <limits>
#include <string>
#include <utility>
#include <vector>

#define COLOR_RED true
#define COLOR_BLACK false

namespace s21 {

template <typename Key, typename T>
class map {
 public:
  class MapConstIterator;
  class MapIterator;

 private:
  struct Node;

  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;
  using iterator = MapIterator;
  using const_iterator = MapConstIterator;

 public:
  map();
  map(std::initializer_list<value_type> const& items);
  map(const map& m);
  map(map&& m) noexcept;
  ~map();

  map& operator=(map&& m) noexcept;

  T& at(const Key& key);
  T& operator[](const Key& key);
  bool contains(const Key& key) const;

  iterator find(const Key& key);
  iterator begin() { return iterator(((root) ? root->min() : nullptr), this); }
  iterator end() { return iterator(nullptr, this); }
  const_iterator cbegin() const {
    return const_iterator(((root) ? root->min() : nullptr), this);
  }
  const_iterator cend() const { return const_iterator(nullptr, this); }

  bool empty() const { return size_ == 0; }
  size_type size() const { return size_; }
  size_type max_size() const;

  void clear();
  void erase(iterator pos);
  void swap(map& other);
  void merge(map& other);

  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    return insert(value_type(key, obj));
  }
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
  std::vector<std::pair<iterator, bool>> insert_many() {
    return std::vector<std::pair<iterator, bool>>();
  }

 private:
  Node* root;
  size_type size_ = 0;
};

// Конструктор, принимающий список инициализации
template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<value_type> const& items) : map() {
  for (auto iter = items.begin(); iter != items.end(); iter++) insert(*iter);
}

// Конструктор копирования
template <typename Key, typename T>
map<Key, T>::map(const map& m) : map() {
  if (!m.empty())
    for (auto it = m.cbegin(); it != m.cend(); it++) insert(*it);
}

// Конструктор перемещения
template <typename Key, typename T>
map<Key, T>::map(map&& m) noexcept : map() {
  swap(m);
}

// Оператор присваивания с перемещением
template <typename Key, typename T>
map<Key, T>& map<Key, T>::operator=(map&& m) noexcept {
  if (this != &m) {
    clear();  // Очищаем текущий объект
    swap(m);  // Меняем содержимое текущего объекта с m
  }
  return *this;
}

// Оператор доступа по ключу
template <typename Key, typename T>
T& map<Key, T>::operator[](const Key& key) {
  return (*(insert(key, T()).first)).second;
}

// Оператор доступа по ключу
template <typename Key, typename T>
map<Key, T>::~map() {
  clear();
}

// Конструктор по умолчанию
template <typename Key, typename T>
map<Key, T>::map() : root(nullptr), size_(0) {}

}  // namespace s21

#include "s21_map_const_iterator.h"
#include "s21_map_iterator.h"
#include "s21_map_metods.h"
#include "s21_map_node.h"

#endif  // S21_MAP_H