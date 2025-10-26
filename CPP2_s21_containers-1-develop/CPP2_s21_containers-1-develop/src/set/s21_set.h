#ifndef S21_SET_H
#define S21_SET_H

#include <cstddef>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "../map/s21_map.h"

namespace s21 {

template <typename Key>
class set {
 public:
  class SetIterator;
  class SetConstIterator;

  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;
  using iterator = SetIterator;
  using const_iterator = SetConstIterator;

 public:
  set() : map_(new map<Key, char>()){};
  set(std::initializer_list<value_type> const& items) : set() {
    for (auto i = items.begin(); i != items.end(); i++) insert(*i);
  }
  set(const set& s) : map_(new map<Key, char>(*(s.map_))){};
  set(set&& s) : map_(new map<Key, char>(std::move(*(s.map_)))){};
  ~set() { delete map_; }
  set& operator=(set&& s) {
    map_->swap(*(s.map_));
    return *this;
  }

  bool contains(const Key& key) const { return map_->contains(key); }
  iterator find(const Key& key) { return iterator(map_->find(key)); }
  iterator begin() { return iterator(map_->begin()); }
  iterator end() { return iterator(map_->end()); }
  const_iterator cbegin() { return const_iterator(map_->begin()); }
  const_iterator cend() { return const_iterator(map_->end()); }

  bool empty() const { return map_->empty(); }
  size_type size() const { return map_->size(); }
  size_type max_size() const { return map_->max_size(); }

  void clear() { map_->clear(); }
  void erase(iterator pos) { map_->erase(pos.map_iter); }
  void swap(set& other) { map_->swap(*(other.map_)); }
  void merge(set& other) { map_->merge(*(other.map_)); }

  std::pair<iterator, bool> insert(const value_type& value) {
    auto resp = map_->insert(std::pair<Key, char>(value, ' '));
    return std::pair<iterator, bool>(iterator(resp.first), resp.second);
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    return std::vector{insert(args)...};
  }
  std::vector<std::pair<iterator, bool>> insert_many() {
    return std::vector<std::pair<iterator, bool>>();
  }

 private:
  map<Key, char>* map_;
};

};  // namespace s21

#include "s21_set_const_iterator.h"
#include "s21_set_iterator.h"

#endif  // S21_SET_H