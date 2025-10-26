#ifndef S21_MULTISET_CONST_ITERATOR_H
#define S21_MULTISET_CONST_ITERATOR_H

#include "s21_multiset.h"

namespace s21 {

template <typename Key>
class multiset<Key>::MultisetConstIterator {
 public:
  MultisetConstIterator(typename map<Key, int>::MapIterator iter, int num)
      : map_iter(iter), num(num) {}

  const_reference operator*() { return (*map_iter).first; }
  MultisetConstIterator& operator++() {
    if (!map_iter.is_end() && (*map_iter).second >= num + 2) {
      num++;
    } else {
      ++map_iter;
      num = 0;
    }
    return *this;
  }
  MultisetConstIterator operator++(int) {
    return (!map_iter.is_end() && (*map_iter).second >= num + 2)
               ? MultisetConstIterator(map_iter, num++)
               : MultisetConstIterator(map_iter++, (num = 0));
  }
  MultisetConstIterator& operator--() {
    if (num <= 0) {
      --map_iter;
      num = (map_iter.is_end()) ? 0 : (*map_iter).second - 1;
    } else {
      num--;
    }
    return *this;
  }
  MultisetConstIterator operator--(int) {
    return (num <= 0)
               ? MultisetConstIterator(
                     map_iter--,
                     (num = (map_iter.is_end()) ? 0 : (*map_iter).second - 1))
               : MultisetConstIterator(map_iter, num--);
  }

  bool operator==(const MultisetConstIterator& other) const {
    return map_iter == other.map_iter && num == other.num;
  }
  bool operator!=(const MultisetConstIterator& other) const {
    return map_iter != other.map_iter || num != other.num;
  }

 private:
  typename map<Key, int>::MapIterator map_iter;
  int num;
};

}  // namespace s21

#endif  // S21_MULTISET_CONST_ITERATOR_H
