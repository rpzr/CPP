#ifndef S21_SET_ITERATOR_H
#define S21_SET_ITERATOR_H

#include "s21_set.h"

namespace s21 {

template <typename Key>
class set<Key>::SetIterator {
 public:
  SetIterator(typename map<Key, char>::MapIterator iter) : map_iter(iter){};

  const_reference operator*() { return (*map_iter).first; }
  SetIterator& operator++() {
    ++map_iter;
    return *this;
  }
  SetIterator operator++(int) { return SetIterator(map_iter++); }
  SetIterator& operator--() {
    --map_iter;
    return *this;
  }
  SetIterator operator--(int) { return SetIterator(map_iter--); }

  bool operator==(const SetIterator& other) const {
    return map_iter == other.map_iter;
  }
  bool operator!=(const SetIterator& other) const {
    return map_iter != other.map_iter;
  }

  typename map<Key, char>::MapIterator map_iter;
};

};  // namespace s21

#endif  // S21_SET_ITERATOR_H