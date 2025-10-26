#ifndef S21_MULTISET_ITERATOR_H
#define S21_MULTISET_ITERATOR_H

#include "s21_multiset.h"

namespace s21 {

template <typename Key>
class multiset<Key>::MultisetIterator {
 public:
  MultisetIterator(typename map<Key, int>::MapIterator iter, int num)
      : map_iter(iter), num(num) {}

  const_reference operator*() { return (*map_iter).first; }
  MultisetIterator& operator++() {
    if (!map_iter.is_end() && (*map_iter).second >= num + 2) {
      num++;
    } else {
      ++map_iter;
      num = 0;
    }
    return *this;
  }
  MultisetIterator operator++(int) {
    return (!map_iter.is_end() && (*map_iter).second >= num + 2)
               ? MultisetIterator(map_iter, num++)
               : MultisetIterator(map_iter++, (num = 0));
  }
  MultisetIterator& operator--() {
    if (num <= 0) {
      --map_iter;
      num = (map_iter.is_end()) ? 0 : (*map_iter).second - 1;
    } else {
      num--;
    }
    return *this;
  }
  MultisetIterator operator--(int) {
    return (num <= 0)
               ? MultisetIterator(
                     map_iter--,
                     (num = (map_iter.is_end()) ? 0 : (*map_iter).second - 1))
               : MultisetIterator(map_iter, num--);
  }
  bool operator==(const MultisetIterator& other) const {
    return map_iter == other.map_iter && num == other.num;
  }
  bool operator!=(const MultisetIterator& other) const {
    return map_iter != other.map_iter || num != other.num;
  }

 public:
  typename map<Key, int>::MapIterator map_iter;

 private:
  int num;
};

}  // namespace s21

#endif  // S21_MULTISET_ITERATOR_H
