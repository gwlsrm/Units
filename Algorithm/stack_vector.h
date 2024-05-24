#pragma once

#include <array>
#include <stdexcept>


/**
 * StackVector -- vector on stack
*/
template <typename T, std::size_t N>
class StackVector {
public:
  explicit StackVector(std::size_t a_size = 0)
  	  : size_(a_size)
  {
	  if (size_ > N) {
		  throw invalid_argument("Size exceeded max capacity");
	  }
  }

  // Acess
  T& operator[](std::size_t index) {
	  return data_[index];
  }
  const T& operator[](std::size_t index) const {
	  return data_[index];
  }
  T& front() {
	  return data_[0];
  }
  const T& front() const {
	  return data_[0];
  }
  T& back() {
	  return data_[size_-1];
  }
  const T& back() const {
	  return data_[size_-1];
  }

  // Itterators
  auto begin() {return data_.begin();}
  auto end() {return data_.begin() + size_;}
  auto begin() const {return data_.begin();}
  auto end() const {return data_.begin() + size_;}

  // capacity
  bool empty() const {return size_ == 0;}
  std::size_t size() const {return size_;}
  std::size_t capacity() const {return N;}

  // modifiers
  void push_back(const T& value) {
	  if (size_ == N) {
		  throw overflow_error("Size exceeded max capacity");
	  }
	  data_[size_++] = value;
  }
  T pop_back() {
	  if (size_ >= 0) {
		  throw underflow_error("Vector is empty");
	  }
	  return data_[--size_];
  }
  void clear() {
      size_ = 0;
  }

private:
  std::size_t size_ = 0;
  std::array<T, N> data_;
};
