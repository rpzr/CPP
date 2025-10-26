#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <initializer_list>
#include <stdexcept>

namespace s21 {
template <typename T, std::size_t N>
class array {
 public:
  // Array Member Type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 private:
  value_type data_[N]{};

 public:
  // Array Member functions
  array() = default;
  array(std::initializer_list<value_type> const &items);
  array(const array &a);
  array(array &&a) : array(a) {}
  ~array() = default;
  array &operator=(array &&a);

  // Array Element access
  reference at(size_type pos);
  reference operator[](size_type pos) { return data_[pos]; }
  const_reference front() { return data_[0]; }
  const_reference back() { return data_[N - 1]; }
  iterator data() { return data_; }

  // Array Iterators
  iterator begin() { return data_; }
  iterator end() { return data_ + N; }
  const_iterator cbegin() const { return data_; }
  const_iterator cend() const { return data_ + N; }

  // Array Capacity
  bool empty() { return N == 0; }
  size_type size() const noexcept { return N; }
  size_type max_size() const noexcept { return N; }

  // Array Modifiers
  void swap(array &other) noexcept;
  void fill(const_reference value) noexcept;
};

template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
  if (items.size() > N) {
    throw std::out_of_range("too many initializer values");
  }
  std::copy(items.begin(), items.end(), data_);
}

template <typename T, std::size_t N>
array<T, N>::array(const array &a) {
  std::copy(a.cbegin(), a.cend(), data_);
}

template <typename T, std::size_t N>
array<T, N> &array<T, N>::operator=(array &&a) {
  if (this != &a) {
    std::move(a.begin(), a.end(), begin());
  }
  return *this;
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= N) {
    throw std::out_of_range("Wrong index");
  }
  return data_[pos];
}

template <typename T, std::size_t N>
void array<T, N>::swap(array &other) noexcept {
  for (size_type i = 0; i < N; ++i) {
    value_type tmp = data_[i];
    data_[i] = other.data_[i];
    other.data_[i] = tmp;
  }
}

template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) noexcept {
  for (iterator it = begin(); it != end(); ++it) {
    *it = value;
  }
}
}  // namespace s21

#endif