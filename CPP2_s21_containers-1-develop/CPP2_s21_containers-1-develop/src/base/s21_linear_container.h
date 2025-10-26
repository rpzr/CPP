#ifndef CPP_LINEAR_CONTAINER_H_
#define CPP_LINEAR_CONTAINER_H_

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace s21 {

template <typename T>
class LinearContainer {
 protected:
  struct Node {
    T data;
    Node* prev;
    Node* next;
    Node(const T& val) : data(val), prev(nullptr), next(nullptr) {}
  };

  Node* head_ = nullptr;
  Node* tail_ = nullptr;
  std::size_t size_ = 0;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  LinearContainer() = default;
  virtual ~LinearContainer() { clear(); }

  bool empty() const { return size_ == 0; }
  size_type size() const { return size_; }

  void clear() {
    while (!empty()) pop_front_node();
  }

  void swap_nodes(LinearContainer& other) {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
  }

  void clone_from(const LinearContainer& other) {
    clear();
    for (Node* curr = other.head_; curr != nullptr; curr = curr->next) {
      push_back_node(curr->data);
    }
  }

  class Iterator {
   public:
    Iterator(Node* node) : node_(node) {}

    value_type& operator*() { return node_->data; }

    Iterator& operator++() {
      if (node_) node_ = node_->next;
      return *this;
    }

    Iterator& operator--() {
      if (node_) node_ = node_->prev;
      return *this;
    }

    bool operator!=(const Iterator& other) const {
      return node_ != other.node_;
    }

    bool operator==(const Iterator& other) const {
      return node_ == other.node_;
    }

   private:
    Node* node_;
  };

  Iterator begin() const { return Iterator(head_); }
  Iterator end() const { return Iterator(nullptr); }

 protected:
  void push_back_node(const T& val) {
    Node* new_node = new Node(val);
    new_node->prev = tail_;
    if (tail_) {
      tail_->next = new_node;
    } else {
      head_ = new_node;
    }
    tail_ = new_node;
    ++size_;
  }

  void push_front_node(const T& val) {
    Node* new_node = new Node(val);
    new_node->next = head_;
    if (head_) {
      head_->prev = new_node;
    } else {
      tail_ = new_node;
    }
    head_ = new_node;
    ++size_;
  }

  void pop_front_node() {
    if (empty()) throw std::out_of_range("Container is empty");
    Node* temp = head_;
    head_ = head_->next;
    if (head_)
      head_->prev = nullptr;
    else
      tail_ = nullptr;
    delete temp;
    --size_;
  }

  void pop_back_node() {
    if (empty()) throw std::out_of_range("Container is empty");
    Node* temp = tail_;
    tail_ = tail_->prev;
    if (tail_)
      tail_->next = nullptr;
    else
      head_ = nullptr;
    delete temp;
    --size_;
  }

  // insert_many (bonus part)
  template <typename... Args>
  void push_many_back_nodes(Args&&... args) {
    (push_back_node(std::forward<Args>(args)), ...);
  }

  template <typename... Args>
  void push_many_front_nodes(Args&&... args) {
    (push_front_node(std::forward<Args>(args)), ...);
  }
};

}  // namespace s21

#endif  // CPP_LINEAR_CONTAINER_H_
