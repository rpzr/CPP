#ifndef S21_LIST_H
#define S21_LIST_H

#include <limits>
#include <stdexcept>
#include <utility>

namespace s21 {
template <typename T>
class list {
 public:
  class ListIterator;
  class ListConstIterator;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  list() : head_(nullptr), tail_(nullptr), size_(0){};
  list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l) noexcept;
  ~list();

  list &operator=(list &&l) noexcept;

  iterator begin() { return iterator(head_); }

  iterator end() { return iterator(nullptr); }

  const_iterator begin() const { return const_iterator(head_); }
  const_iterator end() const { return const_iterator(nullptr); }

  const_reference front() {
    if (!head_) throw std::out_of_range("List is empty");

    return head_->data;
  }
  const_reference back() {
    if (!tail_) throw std::out_of_range("List is empty");

    return tail_->data;
  };

  bool empty() const { return size_ == 0; }
  size_type size() const { return size_; }
  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(Node);
  }

  void clear();
  iterator insert(iterator pos, const_reference value);

  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other) noexcept;
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

  template <typename... Args>
  iterator insert_many(iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);
  template <typename... Args>
  void insert_many_front(Args &&...args);

 private:
  struct Node {
    value_type data;
    Node *next;
    Node *prev;

    explicit Node(const_reference val)
        : data(val), next(nullptr), prev(nullptr) {}
  };

  Node *head_;
  Node *tail_;
  size_type size_;

  Node *merge(Node *first, Node *second);
  Node *mergeSortRecursive(Node *head_node);

 public:
  class ListIterator {
   public:
    ListIterator(Node *node) : node_(node) {}

    value_type &operator*() { return node_->data; }
    ListIterator &operator++() {
      if (node_) {
        node_ = node_->next;
      }
      return *this;
    }
    ListIterator operator++(int) {
      iterator old_it = *this;
      if (node_) {
        node_ = node_->next;
      }
      return old_it;
    }
    ListIterator &operator--() {
      if (node_) {
        node_ = node_->prev;
      }
      return *this;
    }
    ListIterator operator--(int) {
      iterator old_it = *this;
      if (node_) {
        node_ = node_->prev;
      }
      return old_it;
    }
    bool operator!=(const ListIterator &other) const {
      return node_ != other.node_;
    }
    bool operator==(const ListIterator &other) const {
      return node_ == other.node_;
    }

   private:
    Node *node_;
    friend class list;
  };

  class ListConstIterator {
   public:
    ListConstIterator(const Node *node) : node_(node) {}
    ListConstIterator(const ListIterator &it) : node_(it.node_) {}

    const value_type &operator*() const { return node_->data; }
    ListConstIterator &operator++() {
      if (node_) {
        node_ = node_->next;
      }
      return *this;
    }
    ListConstIterator operator++(int) {
      const_iterator old_it = *this;
      if (node_) {
        node_ = node_->next;
      }
      return old_it;
    }
    ListConstIterator &operator--() {
      if (node_) {
        node_ = node_->prev;
      }
      return *this;
    }
    ListConstIterator operator--(int) {
      iterator old_it = *this;
      if (node_) {
        node_ = node_->prev;
      }
      return old_it;
    }
    bool operator!=(const ListConstIterator &other) const {
      return node_ != other.node_;
    }
    bool operator==(const ListConstIterator &other) const {
      return node_ == other.node_;
    }

   private:
    const Node *node_;
    friend class list;
  };
};

template <typename T>
list<T>::list(size_type n) : head_(nullptr), tail_(nullptr), size_(0) {
  if (n > max_size()) {
    throw std::length_error("cannot create std::list larger than max_size()");
  }
  for (size_type i = 0; i < n; i++) {
    push_back(T{});
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items)
    : head_(nullptr), tail_(nullptr), size_(0) {
  for (const auto &item : items) {
    push_back(item);
  }
}

template <typename T>
list<T>::list(const list &l) : head_(nullptr), tail_(nullptr), size_(0) {
  for (const auto &item : l) {
    push_back(item);
  }
}

template <typename T>
list<T>::list(list &&l) noexcept
    : head_(l.head_), tail_(l.tail_), size_(l.size_) {
  l.head_ = nullptr;
  l.tail_ = nullptr;
  l.size_ = 0;
}

template <typename T>
list<T>::~list() {
  clear();
}

template <typename T>
list<T> &list<T>::operator=(list &&l) noexcept {
  if (this != &l) {
    clear();

    head_ = l.head_;
    tail_ = l.tail_;
    size_ = l.size_;

    l.head_ = l.tail_ = nullptr;
    l.size_ = 0;
  }

  return *this;
}

template <typename T>
void list<T>::clear() {
  while (head_) {
    Node *temp = head_;
    head_ = head_->next;
    delete temp;
  }
  tail_ = nullptr;
  size_ = 0;
}

template <typename T>
void list<T>::erase(iterator pos) {
  if (empty() || pos == end() || pos.node_ == nullptr) return;
  if (size_ == 1) {
    delete head_;
    head_ = tail_ = nullptr;
    size_ = 0;
  } else {
    if (pos.node_ == head_) {
      pop_front();
    } else if (pos.node_ == tail_) {
      pop_back();
    } else {
      Node *node_to_delete = pos.node_;
      (pos.node_->prev)->next = pos.node_->next;
      (pos.node_->next)->prev = pos.node_->prev;

      delete node_to_delete;
      size_--;
    }
  }
}

template <typename T>
void list<T>::push_back(const_reference value) {
  Node *new_node = new Node(value);
  if (head_) {
    tail_->next = new_node;
    new_node->prev = tail_;
  } else {
    head_ = new_node;
  }
  tail_ = new_node;
  size_++;
}

template <typename T>
void list<T>::pop_back() {
  if (empty()) return;
  if (size_ == 1) {
    delete tail_;
    head_ = tail_ = nullptr;
  } else {
    Node *prev_tail = tail_->prev;
    prev_tail->next = nullptr;
    delete tail_;
    tail_ = prev_tail;
  }
  size_--;
}

template <typename T>
void list<T>::push_front(const_reference value) {
  Node *new_node = new Node(value);
  if (empty()) {
    head_ = tail_ = new_node;
  } else {
    new_node->next = head_;
    head_->prev = new_node;
    head_ = new_node;
  }
  ++size_;
}

template <typename T>
void list<T>::pop_front() {
  if (empty()) return;
  if (size_ == 1) {
    delete head_;
    head_ = tail_ = nullptr;
  } else {
    Node *old_head = head_;
    head_ = head_->next;
    head_->prev = nullptr;
    delete old_head;
  }

  size_--;
}

template <typename T>
void list<T>::swap(list &other) noexcept {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template <typename T>
void list<T>::merge(list &other) {
  if (this == &other || other.empty()) {
    return;
  }

  if (this->empty()) {
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;

    other.head_ = other.tail_ = nullptr;
    other.size_ = 0;
    return;
  }

  Node *this_current = head_;
  Node *other_current = other.head_;

  while (this_current != nullptr && other_current != nullptr) {
    if (other_current->data <= this_current->data) {
      Node *next_other = other_current->next;

      if (other_current->prev) {
        other_current->prev->next = other_current->next;
      } else {
        other.head_ = other_current->next;
      }
      if (other_current->next) {
        other_current->next->prev = other_current->prev;
      } else {
        other.tail_ = other_current->prev;
      }

      other_current->prev = this_current->prev;
      other_current->next = this_current;

      if (this_current->prev) {
        this_current->prev->next = other_current;
      } else {
        head_ = other_current;
      }
      this_current->prev = other_current;

      other_current = next_other;
      other.size_--;
      size_++;
    } else {
      this_current = this_current->next;
    }
  }

  if (other_current != nullptr) {
    tail_->next = other_current;
    other_current->prev = tail_;
    tail_ = other.tail_;
    size_ += other.size_;

    other.head_ = other.tail_ = nullptr;
    other.size_ = 0;
  }
}

template <typename T>
void list<T>::splice(const_iterator pos, list &other) {
  if (this == &other || other.empty()) {
    return;
  }

  Node *other_head = other.head_;
  Node *other_tail = other.tail_;

  Node *pos_node = const_cast<Node *>(pos.node_);

  if (empty()) {
    head_ = other_head;
    tail_ = other_tail;
  } else {
    if (pos_node == head_) {
      // Вставка перед head
      other_tail->next = head_;
      head_->prev = other_tail;
      head_ = other_head;
    } else {
      Node *prev_node = (pos_node == nullptr) ? tail_ : pos_node->prev;

      // Связываем хвост other с pos_node
      other_tail->next = pos_node;
      if (pos_node) pos_node->prev = other_tail;

      // Связываем предыдущий узел с головой other
      prev_node->next = other_head;
      other_head->prev = prev_node;

      // Обновляем tail если вставляем в конец
      if (pos_node == nullptr) tail_ = other_tail;
    }
  }

  size_ += other.size_;
  other.size_ = 0;
  other.head_ = other.tail_ = nullptr;
}

template <typename T>
void list<T>::reverse() {
  if (size_ <= 1) return;

  for (Node *cur = head_; cur != nullptr; cur = cur->prev) {
    std::swap(cur->next, cur->prev);
  }

  std::swap(head_, tail_);
}

template <typename T>
void list<T>::unique() {
  if (size_ <= 1) return;

  iterator current_it = begin();
  iterator next_it = current_it;
  ++next_it;
  while (next_it != end()) {
    if (*current_it == *next_it) {
      Node *node_after_delete = next_it.node_->next;
      erase(next_it);
      next_it = iterator(node_after_delete);
    } else if (next_it != nullptr) {
      current_it = next_it;
      ++next_it;
    }
  }
}

template <typename T>
typename list<T>::Node *list<T>::merge(Node *first, Node *second) {
  if (!first) return second;
  if (!second) return first;

  Node *result_head = nullptr;
  if (first->data <= second->data) {
    result_head = first;
    first = first->next;
  } else {
    result_head = second;
    second = second->next;
  }

  result_head->prev = nullptr;
  Node *current_tail = result_head;

  while (first && second) {
    if (first->data <= second->data) {
      current_tail->next = first;
      first->prev = current_tail;
      current_tail = current_tail->next;
      first = first->next;
    } else {
      current_tail->next = second;
      second->prev = current_tail;
      current_tail = current_tail->next;
      second = second->next;
    }
  }

  if (first) {
    current_tail->next = first;
    first->prev = current_tail;
  } else {
    current_tail->next = second;
    second->prev = current_tail;
  }

  return result_head;
}

template <typename T>
typename list<T>::Node *list<T>::mergeSortRecursive(Node *head_node) {
  if (!head_node || !head_node->next) return head_node;

  Node *slow = head_node;
  Node *fast = head_node->next;

  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
  }

  Node *right = slow->next;
  if (right) right->prev = nullptr;

  slow->next = nullptr;
  Node *left = head_node;

  left = mergeSortRecursive(left);
  right = mergeSortRecursive(right);

  return merge(left, right);
}

template <typename T>
void list<T>::sort() {
  if (size_ <= 1) return;

  head_ = mergeSortRecursive(head_);

  tail_ = head_;
  while (tail_ && tail_->next != nullptr) {
    tail_ = tail_->next;
  }
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  if (pos == end()) {
    push_back(value);
    return iterator(tail_);
  } else if (pos == begin()) {
    push_front(value);
    return iterator(head_);
  } else if (pos.node_) {
    Node *new_node = new Node(value);
    Node *current = pos.node_;

    new_node->prev = current->prev;
    new_node->next = current;

    current->prev->next = new_node;
    current->prev = new_node;

    size_++;
    return iterator(new_node);
  }

  return pos;
}

// Вставка нескольких элементов в список перед указанной позицией
template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(iterator pos, Args &&...args) {
  (insert(pos, std::forward<Args>(args)), ...);
  return pos;
}

// Вставка нескольких элементов в конец списка
template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args &&...args) {
  (push_back(std::forward<Args>(args)), ...);
}

// Вставка нескольких элементов в начало списка
template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args &&...args) {
  (push_front(std::forward<Args>(args)), ...);
}

}  // namespace s21

#endif