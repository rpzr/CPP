#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include <cstddef>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "../map/s21_map.h"

namespace s21 {

template <typename Key>
class multiset {
 public:
  class MultisetIterator;
  class MultisetConstIterator;

  using iterator = MultisetIterator;
  using const_iterator = MultisetIterator;
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

  multiset() : map_(new map<Key, int>()) {}
  multiset(std::initializer_list<value_type> const& items) : multiset() {
    for (auto i = items.begin(); i != items.end(); i++) insert(*i);
    size_ = items.size();
  }
  multiset(const multiset& s) : map_(new map<Key, int>(*(s.map_))) {
    size_ = s.size_;
  }
  multiset(multiset&& s) noexcept
      : map_(new map<Key, int>(std::move(*(s.map_)))) {
    std::swap(size_, s.size_);
  }
  ~multiset() { delete map_; }
  multiset& operator=(multiset&& s) noexcept {
    map_->swap(*(s.map_));
    std::swap(size_, s.size_);
    return *this;
  }

  bool contains(const Key& key) const { return map_->contains(key); }
  size_type count(const Key& key) const {
    return (map_->find(key) != map_->end()) ? (*(map_->find(key))).second : 0;
  }

  std::pair<iterator, iterator> equal_range(const Key& key) {
    return std::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
  }

  iterator lower_bound(const Key& key) const {
    return iterator(map_->find(key), 0);
  }

  iterator upper_bound(const Key& key) const {
    return iterator(map_->find(key), (map_->find(key) != map_->end())
                                         ? (*(map_->find(key))).second - 1
                                         : 0);
  }

  iterator find(const Key& key) { return lower_bound(key); }
  iterator begin() { return iterator(map_->begin(), 0); }
  iterator end() { return iterator(map_->end(), 0); }
  iterator cbegin() { return const_iterator(map_->begin(), 0); }
  iterator cend() { return const_iterator(map_->end(), 0); }

  bool empty() const { return map_->empty(); }
  size_type size() const { return size_; }
  size_type max_size() const { return map_->max_size(); }

  void clear() {
    map_->clear();
    size_ = 0;
  }

  void erase(iterator pos) {
    size_--;
    if (count(*pos) <= 1) {
      map_->erase(pos.map_iter);
    } else {
      (*(pos.map_iter)).second--;
    }
  }

  void swap(multiset& other) {
    map_->swap(*(other.map_));
    std::swap(size_, other.size_);
  }

  void merge(multiset& other) {
    for (auto iter = other.begin(); iter != other.end(); ++iter) {
      insert(*iter);
    }
  }

  iterator insert(const value_type& value) {
    size_++;
    auto resp = map_->insert(std::pair<Key, int>(value, 1));
    if (!resp.second) (*(resp.first)).second++;
    return iterator(resp.first, (*(resp.first)).second);
  };

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> result;
    result.reserve(sizeof...(args));
    (result.emplace_back(insert(std::forward<Args>(args)), true), ...);
    return result;
  }

 private:
  map<Key, int>* map_;
  size_type size_ = 0;
};

}  // namespace s21

#include "s21_multiset_const_iterator.h"
#include "s21_multiset_iterator.h"

#endif  // S21_MULTISET_H