#ifndef CPP_QUEUE_H_
#define CPP_QUEUE_H_

#include <initializer_list>
#include <stdexcept>
#include <utility>

#include "../base/s21_linear_container.h"

namespace s21 {

template <typename T>
class queue : public LinearContainer<T> {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;
  using Iterator = typename LinearContainer<T>::Iterator;

  using typename LinearContainer<T>::Node;
  using LinearContainer<T>::head_;
  using LinearContainer<T>::tail_;
  using LinearContainer<T>::size_;
  using LinearContainer<T>::push_back_node;
  using LinearContainer<T>::pop_front_node;
  using LinearContainer<T>::clear;
  using LinearContainer<T>::swap_nodes;
  using LinearContainer<T>::clone_from;

  queue() = default;

  queue(std::initializer_list<value_type> const& items) {
    for (const auto& item : items) push(item);
  }

  queue(const queue& other) { this->clone_from(other); }

  queue(queue&& other) noexcept {
    swap_nodes(other);
    other.head_ = other.tail_ = nullptr;
    other.size_ = 0;
  }

  queue& operator=(queue&& other) noexcept {
    if (this != &other) {
      clear();
      swap_nodes(other);
      other.head_ = other.tail_ = nullptr;
      other.size_ = 0;
    }
    return *this;
  }

  ~queue() = default;

  const_reference front() const {
    if (this->empty()) throw std::out_of_range("Queue is empty");
    return this->head_->data;
  }

  const_reference back() const {
    if (this->empty()) throw std::out_of_range("Queue is empty");
    return this->tail_->data;
  }

  void push(const_reference value) { push_back_node(value); }

  void pop() { pop_front_node(); }

  void swap(queue& other) { swap_nodes(other); }

  Iterator begin() const { return Iterator(this->head_); }
  Iterator end() const { return Iterator(nullptr); }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    this->push_many_back_nodes(std::forward<Args>(args)...);
  }
};

}  // namespace s21

#endif  // CPP_QUEUE_H_
