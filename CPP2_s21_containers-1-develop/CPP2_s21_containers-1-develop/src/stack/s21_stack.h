#ifndef CPP_STACK_H_
#define CPP_STACK_H_

#include <initializer_list>
#include <stdexcept>
#include <utility>

#include "../base/s21_linear_container.h"

namespace s21 {

template <typename T>
class stack : public LinearContainer<T> {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;
  using Iterator = typename LinearContainer<T>::Iterator;

  using typename LinearContainer<T>::Node;
  using LinearContainer<T>::head_;
  using LinearContainer<T>::size_;
  using LinearContainer<T>::push_front_node;
  using LinearContainer<T>::pop_front_node;
  using LinearContainer<T>::clear;
  using LinearContainer<T>::swap_nodes;
  using LinearContainer<T>::clone_from;

  stack() = default;

  stack(std::initializer_list<value_type> const& items) {
    for (auto it = items.begin(); it != items.end(); ++it) {
      push(*it);
    }
  }

  stack(const stack& other) { this->clone_from(other); }

  stack(stack&& other) noexcept {
    swap_nodes(other);
    other.head_ = nullptr;
    other.size_ = 0;
  }

  stack& operator=(stack&& other) noexcept {
    if (this != &other) {
      clear();
      swap_nodes(other);
      other.head_ = nullptr;
      other.size_ = 0;
    }
    return *this;
  }

  ~stack() = default;

  void push(const_reference value) { push_front_node(value); }

  void pop() { pop_front_node(); }

  const_reference top() const {
    if (this->empty()) throw std::out_of_range("Stack is empty");
    return this->head_->data;
  }

  void swap(stack& other) { swap_nodes(other); }

  Iterator begin() const { return Iterator(this->head_); }
  Iterator end() const { return Iterator(nullptr); }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    this->push_many_front_nodes(std::forward<Args>(args)...);
  }
};

}  // namespace s21

#endif  // CPP_STACK_H_
