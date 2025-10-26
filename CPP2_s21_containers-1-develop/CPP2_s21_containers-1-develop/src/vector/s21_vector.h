#ifndef S21_VECTOR_H
#define S21_VECTOR_H
#include <initializer_list>
#include <limits>
#include <stdexcept>

namespace s21 {
template <typename T>
class vector {
 public:
  // Vector Member Type
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

  // Constructors, destructor
  vector() = default;
  vector(size_type len);
  vector(const vector& other);
  vector(vector&& other);
  vector(std::initializer_list<T> const& items);
  ~vector() { delete[] data_; }

  // Operators
  vector& operator=(const vector& other);
  vector& operator=(vector&& other);

  // Vector Element Access
  reference operator[](size_t pos) { return data_[pos]; }
  reference at(size_type pos) const;
  const_reference front() const { return data_[0]; }
  const_reference back() const { return data_[size_ - 1]; }
  value_type* data() const { return data_; }

  // Vector Iterators
  iterator begin() { return data_; }
  iterator end() { return data_ + size_; }
  const_iterator cbegin() const { return data_; }
  const_iterator cend() const { return data_ + size_; }

  // Vector Capacity
  bool empty() const { return size_ == 0; }
  size_type size() const { return size_; }
  size_type max_size() const {
    return std::numeric_limits<std::size_t>::max() / sizeof(value_type) / 2;
  }
  void reserve(size_type size);
  size_type capacity() const { return capacity_; }
  void shrink_to_fit();

  // Vector Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector& other);

  // insert_many (bonus part)
  template <typename... Args>
  void insert_many_back(Args&&... args);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);

 private:
  size_type size_{0}, capacity_{0};
  value_type* data_{nullptr};
  bool insert_help(size_type pos_to_insert, size_type num_args);

  void realloc_mem();
};

template <typename T>
void vector<T>::realloc_mem() {
  capacity_ = (capacity_ == 0 ? 1 : capacity_ * 2);
  value_type* new_data_ = new value_type[capacity_];
  for (size_type i = 0; i < size_; ++i) {
    new_data_[i] = data_[i];
  }
  delete[] data_;
  data_ = new_data_;
}

template <typename T>
vector<T>::vector(size_type n) : size_(n), capacity_(n) {
  if (n > max_size()) {
    throw std::length_error("cannot create std::vector larger than max_size()");
  }
  if (n != 0) {
    data_ = new value_type[capacity_]();
  }
}

template <typename T>
vector<T>::vector(const vector& other)
    : size_(other.size_), capacity_(other.capacity_) {
  if (other.size_ != 0) {
    data_ = new value_type[capacity_];
    std::copy(other.cbegin(), other.cend(), data_);
  }
}

template <typename T>
vector<T>::vector(vector&& other)
    : size_(other.size_), capacity_(other.capacity_), data_(other.data_) {
  other.size_ = 0;
  other.capacity_ = 0;
  other.data_ = nullptr;
}

template <typename T>
vector<T>::vector(std::initializer_list<T> const& items) {
  size_ = items.size();
  capacity_ = size_;
  if (size_ != 0) {
    data_ = new value_type[capacity_];
    size_type i = 0;
    for (auto it = items.begin(); it != items.end(); it++) {
      data_[i++] = *it;
    }
  }
}

template <typename T>
vector<T>& vector<T>::operator=(const vector& other) {
  if (this != &other) {
    if (capacity_ < other.capacity_) {
      delete[] data_;
      data_ = new value_type[other.capacity_];
    }
    size_ = other.size_;
    capacity_ = other.capacity_;
    size_type i = 0;
    for (iterator it = begin(); it != end(); ++it) {
      *it = other.data_[i++];
    }
  }
  return *this;
}

template <typename T>
vector<T>& vector<T>::operator=(vector&& other) {
  if (this != &other) {
    delete[] data_;
    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
  }
  return *this;
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) const {
  if (pos >= size_) {
    throw std::out_of_range("Wrong index");
  }
  return data_[pos];
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size > max_size()) {
    throw std::out_of_range("Size > max_size of vector");
  }
  if (size > capacity_) {
    value_type* new_data_ = new value_type[size];
    size_type i = 0;
    for (iterator it = begin(); it != end(); ++it) {
      new_data_[i++] = *it;
    }
    delete[] data_;
    data_ = new_data_;
    capacity_ = size;
  }
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (size_ == 0) {
    delete[] data_;
    data_ = nullptr;
    capacity_ = 0;
  } else if (capacity_ > size_) {
    capacity_ = size_;
    value_type* new_data_ = new value_type[capacity_];
    size_type i = 0;
    for (iterator it = begin(); it != end(); ++it) {
      new_data_[i++] = *it;
    }
    delete[] data_;
    data_ = new_data_;
  }
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  {
    if (size_ >= capacity_) {
      this->realloc_mem();
    }
    data_[size_] = value;
    size_++;
  }
}

template <typename T>
void vector<T>::erase(iterator pos) {
  if (pos >= begin() && pos < end()) {
    pos->~value_type();
    for (iterator it = pos; it != end() - 1; ++it) {
      *it = *(it + 1);
    }
  }
  this->pop_back();
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type offset = pos - begin();
  if (pos < begin() || pos > end()) {
    throw std::out_of_range("Wrong index");
  }

  if (size_ < capacity_) {
    for (iterator it = end(); it != pos; --it) {
      *it = *(it - 1);
    }
    *pos = value;
  } else {
    capacity_ = (capacity_ == 0 ? 1 : capacity_ * 2);
    value_type* new_data_ = new value_type[capacity_];
    size_type i = 0;
    for (iterator it = begin(); it != pos; ++it) {
      new_data_[i++] = *it;
    }
    new_data_[i++] = value;
    for (iterator it = pos; it != end(); ++it) {
      new_data_[i++] = *it;
    }
    delete[] data_;
    data_ = new_data_;
  }
  size_++;
  return begin() + offset;
}

template <typename T>
void vector<T>::swap(vector& other) {
  value_type* tmp_data_ = data_;
  data_ = other.data_;
  other.data_ = tmp_data_;

  size_type tmp_size_ = size_;
  size_ = other.size_;
  other.size_ = tmp_size_;

  size_type tmp_capacity_ = capacity_;
  capacity_ = other.capacity_;
  other.capacity_ = tmp_capacity_;
}

template <typename T>
void vector<T>::clear() {
  for (size_type i = 0; i < size_; ++i) {
    data_[i].~value_type();
  }
  size_ = 0;
}

template <typename T>
void vector<T>::pop_back() {
  if (size_ > 0) {
    data_[size_ - 1].~value_type();
    size_--;
  }
}

template <typename value_type>
bool vector<value_type>::insert_help(size_type pos_to_insert,
                                     size_type num_args) {
  bool flag = false;
  if (pos_to_insert <= size_) {
    flag = true;
    if ((size_ + num_args) >= capacity_) reserve(size_ + num_args);
    size_ += num_args;
    for (size_type i = size_ - 1; i >= pos_to_insert + num_args; --i) {
      data_[i] = data_[i - num_args];
    }
  } else {
    throw std::out_of_range("Index is out of range");
  }
  return flag;
}

template <typename value_type>
template <typename... Args>
void vector<value_type>::insert_many_back(Args&&... args) {
  (push_back(std::forward<Args>(args)), ...);
}

template <typename value_type>
template <typename... Args>
typename vector<value_type>::iterator vector<value_type>::insert_many(
    const_iterator pos, Args&&... args) {
  size_type num_args = sizeof...(Args);
  size_type pos_to_insert = pos - this->cbegin();
  size_type start_pos = pos_to_insert;

  if (insert_help(pos_to_insert, num_args)) {
    (void)std::initializer_list<value_type>{
        (data_[pos_to_insert++] = std::forward<Args>(args), 0)...};
  }

  return iterator(data_ + start_pos);
}

}  // namespace s21

#endif