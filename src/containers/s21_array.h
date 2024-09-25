#ifndef CPP2_S21_CONTAINERS_2_CONTAINERS_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_2_CONTAINERS_S21_ARRAY_H_

namespace s21 {
template <typename T, std::size_t N>
class Array {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using size_type = std::size_t;
  using reverse_iterator = std::reverse_iterator<pointer>;

  Array();
  explicit Array(std::initializer_list<value_type> const &items);
  Array(const Array &other);
  Array(Array &&other);
  ~Array();
  Array<value_type, N> &operator=(const Array &other);
  Array<value_type, N> &operator=(Array &&other);
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  pointer data();
  const_pointer data() const;

  pointer begin();
  pointer end();
  reverse_iterator rbegin();
  reverse_iterator rend();
  size_type size() const;
  size_type max_size() const;
  bool empty() const;

  void fill(const_reference value);
  void swap(Array &other);

 private:
  size_type size_{};
  pointer data_{nullptr};
};

template <typename value_type, std::size_t N>
Array<value_type, N>::Array() : size_{}, data_{new value_type[N]()} {};

template <typename value_type, std::size_t N>
Array<value_type, N>::Array(std::initializer_list<value_type> const &items)
    : size_{items.size()}, data_{new value_type[N]{}} {
  size_type i{};
  for (const auto &item : items) {
    if (i >= N) break;
    data_[i++] = item;
  }
}

template <typename value_type, std::size_t N>
Array<value_type, N>::Array(const Array &other)
    : size_{other.size_}, data_{new value_type[N]} {
  for (size_type i{}; i < size_; ++i) {
    data_[i] = other.data_[i];
  }
}

template <typename value_type, std::size_t N>
Array<value_type, N>::Array(Array &&other)
    : size_{std::move(other.size_)}, data_{std::move(other.data_)} {
  other.size_ = 0;
  other.data_ = nullptr;
}

template <typename value_type, std::size_t N>
Array<value_type, N> &Array<value_type, N>::operator=(Array &&other) {
  if (this != &other) {
    delete[] data_;
    size_ = other.size_;
    data_ = other.data_;
    other.size_ = 0;
    other.data_ = nullptr;
  }
  return *this;
}

template <typename value_type, std::size_t N>
Array<value_type, N> &Array<value_type, N>::operator=(const Array &other) {
  if (this != &other) {
    delete[] data_;
    size_ = other.size_;
    data_ = new value_type[size_];
    for (size_type i{}; i < size_; ++i) {
      data_[i] = other.data_[i];
    }
  }
  return *this;
}

template <typename value_type, std::size_t N>
Array<value_type, N>::~Array() {
  if (data_ != nullptr) {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
  }
}

template <typename value_type, std::size_t N>
typename Array<value_type, N>::pointer Array<value_type, N>::begin() {
  return &data_[0];
}

template <typename value_type, std::size_t N>
typename Array<value_type, N>::pointer Array<value_type, N>::end() {
  return &data_[N];
}

template <typename value_type, std::size_t N>
typename Array<value_type, N>::reverse_iterator Array<value_type, N>::rbegin() {
  return reverse_iterator(&data_[N]);
}

template <typename value_type, std::size_t N>
typename Array<value_type, N>::reverse_iterator Array<value_type, N>::rend() {
  return reverse_iterator(&data_[0]);
}

template <typename value_type, std::size_t N>
typename Array<value_type, N>::reference Array<value_type, N>::operator[](
    size_type pos) {
  return data_[pos];
}

template <typename value_type, std::size_t N>
typename Array<value_type, N>::const_reference Array<value_type, N>::operator[](
    size_type pos) const {
  return data_[pos];
}

template <typename value_type, std::size_t N>
typename Array<value_type, N>::reference Array<value_type, N>::at(
    size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return data_[pos];
}

template <typename value_type, std::size_t N>
typename Array<value_type, N>::const_reference Array<value_type, N>::at(
    size_type pos) const {
  if (pos >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return data_[pos];
}

template <typename value_type, std::size_t N>
typename Array<value_type, N>::reference Array<value_type, N>::front() {
  return data_[0];
}

template <typename value_type, std::size_t N>
typename Array<value_type, N>::const_reference Array<value_type, N>::front()
    const {
  return data_[0];
}

template <typename value_type, std::size_t N>
typename Array<value_type, N>::reference Array<value_type, N>::back() {
  return data_[size_ - 1];
}

template <typename value_type, std::size_t N>
typename Array<value_type, N>::const_reference Array<value_type, N>::back()
    const {
  return data_[size_ - 1];
}

template <typename value_type, std::size_t N>
typename Array<value_type, N>::pointer Array<value_type, N>::data() {
  return data_;
}

template <typename value_type, std::size_t N>
typename Array<value_type, N>::const_pointer Array<value_type, N>::data()
    const {
  return data_;
}

template <typename value_type, std::size_t N>
typename Array<value_type, N>::size_type Array<value_type, N>::size() const {
  return N;
}

template <typename value_type, std::size_t N>
bool Array<value_type, N>::empty() const {
  return size_ == 0;
}

template <typename value_type, std::size_t N>
typename Array<value_type, N>::size_type Array<value_type, N>::max_size()
    const {
  return N;
}

template <typename value_type, std::size_t N>
void Array<value_type, N>::fill(const_reference value) {
  for (std::size_t i{}; i < N; ++i) {
    size_++;
    data_[i] = value;
  }
}

template <typename value_type, std::size_t N>
void Array<value_type, N>::swap(Array &other) {
  if (this != &other) {
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
  }
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_2_CONTAINERS_S21_ARRAY_H_
