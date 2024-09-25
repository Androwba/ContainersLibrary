#ifndef CPP2_S21_CONTAINERS_2_CONTAINERS_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_2_CONTAINERS_S21_VECTOR_H_

#include <limits>
#include <memory>
#include <utility>
namespace s21 {
template <typename T, class Allocator = std::allocator<T>>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;
  using difference_type = size_type;

  vector() = default;

  explicit vector(size_type n, const_reference value = value_type())
      : vector() {
    reserve(n);
    while (n--) push_back(value);
  }

  explicit vector(std::initializer_list<value_type> const &items)
      : size_{items.size()}, capacity_(items.size()) {
    data_ = myAllocator.allocate(capacity_);
    std::copy(items.begin(), items.end(), data_);
  }

  vector(const vector &v) {
    size_ = v.size_;
    capacity_ = v.capacity_;
    data_ = nullptr;
    if (size_ > 0) {
      data_ = myAllocator.allocate(capacity_);
    }
    std::copy(v.begin(), v.end(), data_);
  }

  vector(vector &&v) noexcept {
    size_ = std::exchange(v.size_, 0);
    capacity_ = std::exchange(v.capacity_, 0);
    data_ = std::exchange(v.data_, nullptr);
  }

  ~vector() { myAllocator.deallocate(data_, capacity_); }

  vector &operator=(vector &&v) noexcept {
    if (this != &v) {
      myAllocator.deallocate(data_, capacity_);
      size_ = std::exchange(v.size_, 0);
      if (this->capacity_ < v.capacity_)
        capacity_ = std::exchange(v.capacity_, 0);
      data_ = std::exchange(v.data_, nullptr);
    }
    return *this;
  }

  vector &operator=(vector &v) {
    myAllocator.deallocate(data_, capacity_);
    size_ = v.size_;
    if (this->capacity_ < v.capacity_) capacity_ = v.capacity_;
    data_ = myAllocator.allocate(size_);
    std::copy(v.data_, v.data_ + v.size_, data_);
    return *this;
  }

  reference at(size_type pos) {
    if (pos >= size_) {
      throw std::out_of_range("vector going over the limit");
    }
    return data_[pos];
  }

  const_reference at(size_type pos) const {
    if (pos >= size_) {
      throw std::out_of_range("vector going over the limit");
    }
    return data_[pos];
  }

  reference operator[](size_type pos) { return at(pos); }

  const_reference operator[](size_type pos) const { return at(pos); }

  iterator begin() noexcept { return data_; }

  iterator begin() const noexcept { return data_; }

  iterator end() noexcept { return data_ + size_; }

  iterator end() const noexcept { return data_ + size_; }

  const_reference front() { return *begin(); }

  const_reference front() const { return *begin(); }

  const_reference back() { return *std::prev(end()); }

  const_reference back() const { return *std::prev(end()); }

  iterator data() noexcept { return data_; }

  const_iterator data() const noexcept { return data_; }

  bool empty() const noexcept {
    if (capacity_ == 0) {
      return true;
    } else {
      return false;
    }
  }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept {
    return (std::numeric_limits<difference_type>::max() / sizeof(value_type) /
            2);
  }

  void reserve(size_type size) {
    if (size > max_size()) {
      throw std::out_of_range("vector going over the limit");
    }
    if (size > capacity_) {
      auto *buf = myAllocator.allocate(size);
      for (size_type i = 0; i < size_; i++) buf[i] = std::move(data_[i]);
      myAllocator.deallocate(data_, capacity_);
      data_ = buf;
      capacity_ = size;
    }
  }

  size_type capacity() const noexcept { return capacity_; }

  void shrink_to_fit() {
    if (capacity_ != size_) {
      capacity_ = size_;
      reserve(size_);
    }
  }

  void clear() noexcept { size_ = 0; }

  void push_back(const_reference value) {
    if (size_ == capacity_) {
      reserve(size_ ? size_ * 2 : 1);
    }
    data_[size_] = value;
    ++size_;
  }

  void push_back(value_type &&value) {
    if (size_ == capacity_) {
      reserve(size_ ? size_ * 2 : 1);
    }
    data_[size_] = std::move(value);
    ++size_;
  }

  void pop_back() { --size_; }

  void swap(vector &other) {
    std::swap(data_, other.data_);
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
  }

  iterator insert(iterator pos, const_reference value) {
    size_type temp = pos - begin();
    if (size_ == capacity_) {
      ReserveMemory(size_ ? size_ * 2 : 1);
    }
    std::copy(begin() + temp, end(), data_ + temp + 1);
    *(data_ + temp) = (value);
    ++size_;
    return begin() + temp;
  }

  iterator insert(iterator pos, value_type &&value) {
    size_type temp = pos - begin();
    if (size_ == capacity_) {
      ReserveMemory(size_ ? size_ * 2 : 1);
    }
    std::copy(begin() + temp, end(), data_ + temp + 1);
    *(data_ + temp) = std::move(value);
    ++size_;
    return begin() + temp;
  }

  void erase(iterator pos) {
    iterator buff = myAllocator.allocate(size_ - 1);
    for (size_type i = 0, j = 0; i < size_; i++)
      if ((this->begin() + i) != pos) buff[j++] = this->data_[i];
    myAllocator.deallocate(data_, size());
    data_ = buff;
    --size_;
  }

  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    iterator res = nullptr;
    auto pntr = pos - begin();
    // reserve(capacity_ + sizeof...(args));
    value_type elements[] = {args...};
    for (auto &i : elements) res = insert(begin() + pntr++, i);
    return res;
  }

  template <typename... Args>
  void emplace_back(Args &&...args) {
    value_type elements[] = {args...};
    for (auto &i : elements) push_back(i);
  }

 private:
  iterator data_ = nullptr;
  size_type size_ = 0;
  size_type capacity_ = 0;
  std::allocator<value_type> myAllocator;

  void ReserveMemory(size_type size) {
    iterator temp_data = myAllocator.allocate(size);
    for (size_type i = 0; i < size_; ++i) temp_data[i] = std::move(data_[i]);
    myAllocator.deallocate(data_, capacity_);
    data_ = temp_data;
    capacity_ = size;
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_2_CONTAINERS_S21_VECTOR_H_