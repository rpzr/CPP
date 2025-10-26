#ifndef S21_SET_CONST_ITERATOR_H
#define S21_SET_CONST_ITERATOR_H

#include "s21_set.h"

namespace s21 {

template <typename Key>
class set<Key>::SetConstIterator {
 public:
  SetConstIterator(typename map<Key, char>::MapIterator iter)
      : map_iter(iter){};

  const_reference operator*() { return (*map_iter).first; }
  SetConstIterator& operator++() {
    ++map_iter;
    return *this;
  }
  SetConstIterator operator++(int) { return SetConstIterator(map_iter++); }
  SetConstIterator& operator--() {
    --map_iter;
    return *this;
  }
  SetConstIterator operator--(int) { return SetConstIterator(map_iter--); }

  bool operator==(const SetConstIterator& other) const {
    return map_iter == other.map_iter;
  }
  bool operator!=(const SetConstIterator& other) const {
    return map_iter != other.map_iter;
  }

  typename map<Key, char>::MapIterator map_iter;
};

};  // namespace s21

#endif  // S21_SET_CONST_ITERATOR_H