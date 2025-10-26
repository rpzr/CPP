#ifndef S21_MAP_CONST_ITERATOR_H
#define S21_MAP_CONST_ITERATOR_H

#include "s21_map.h"
namespace s21 {

template <typename Key, typename T>
class map<Key, T>::MapConstIterator {
 public:
  MapConstIterator(Node* node, const map<Key, T>* owner)
      : node_(node), owner(owner) {}
  const_reference operator*() const {
    if (!node_)
      throw std::out_of_range("Trying to access non existing value or end");
    return node_->value;
  }

  MapConstIterator& operator++() {
    node_ = (node_) ? node_->next() : owner->root->min();
    return *this;
  }
  MapConstIterator operator++(int) {
    Node* old = node_;
    this->operator++();
    return MapConstIterator(old, owner);
  }
  MapConstIterator& operator--() {
    node_ = (node_) ? node_->prev() : owner->root->max();
    return *this;
  }
  MapConstIterator operator--(int) {
    Node* old = node_;
    this->operator--();
    return MapConstIterator(old, owner);
  }
  bool operator==(const MapConstIterator& other) const {
    return node_ == other.node_;
  }
  bool operator!=(const MapConstIterator& other) const {
    return node_ != other.node_;
  }

 public:
  Node* node_;

 private:
  const map<Key, T>* owner;
};

}  // namespace s21

#endif  // S21_MAP_CONST_ITERATOR_H