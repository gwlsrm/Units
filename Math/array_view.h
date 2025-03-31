#pragma once

#include <algorithm>
#include <iostream>
#include <stdexcept>

namespace gwmath
{

// ArrayView -- not owning wrapper for memory with vector interface
template <typename T>
class ArrayView {
public:
    ArrayView(std::size_t size, T *data);
    void copyFrom(const ArrayView& a);
    // iterators
    auto begin() { return data_; }
    const auto begin() const { return data_; }
    auto end() { return data_ + size_; }
    const auto end() const { return data_ + size_; }
    // getters
    const T &operator[](std::size_t idx) const {
        return data_[idx];
    }
    T &operator[](std::size_t idx) { return data_[idx]; }
    const T &at(std::size_t idx) const {
        if (idx >= size_)
        {
            throw std::out_of_range("idx is out of range");
        }
        return data_[idx];
    }
    T &at(std::size_t idx) {
        if (idx >= size_)
        {
            throw std::out_of_range("idx is out of range");
        }
        return data_[idx];
    }
    std::size_t size() const { return size_; }
    const T *data() const { return data_; }
    T *data() { return data_; }

private:
    T *data_;
    std::size_t size_ = 0;
};
// operators
template <typename T>
std::ostream &operator<<(std::ostream &out, const ArrayView<T> &a);
template <typename T>
bool operator==(const ArrayView<T> &lhs, const ArrayView<T> &rhs);


// ConstArrayView -- not owning wrapper for memory with vector interface
template <typename T>
class ConstArrayView {
public:
    ConstArrayView(std::size_t size, const T *data);
    // iterators
    const auto begin() const { return data_; }
    const auto end() const { return data_ + size_; }
    // getters
    const T &operator[](std::size_t idx) const {
        return data_[idx];
    }
    const T &at(std::size_t idx) const {
        if (idx >= size_)
        {
            throw std::out_of_range("idx is out of range");
        }
        return data_[idx];
    }
    std::size_t size() const { return size_; }
    const T *data() const { return data_; }

private:
    const T *data_;
    std::size_t size_ = 0;
};
// operators
template <typename T>
std::ostream &operator<<(std::ostream &out, const ConstArrayView<T> &a);
template <typename T>
bool operator==(const ConstArrayView<T> &lhs, const ConstArrayView<T> &rhs);


// realization
template <typename T>
ArrayView<T>::ArrayView(std::size_t size, T* data)
  : data_(data)
  , size_(size)
{}

template <typename T>
void ArrayView<T>::copyFrom(const ArrayView& a) {
    if (this == &a) {
        return;
    }
    if (a.size() != size_) {
        throw std::invalid_argument("Arrays must the same size for copy");
    }
    std::copy(a.begin(), a.end(), data_);
}

// operators
template <typename T>
std::ostream &operator<<(std::ostream &out, const ArrayView<T> &a) {
    out << "[";
    bool is_first = true;
    for (const auto& v : a) {
        if (is_first) {
            is_first = false;
        } else {
            out << ", ";
        }
        out << v;
    }
    out << "]";
    return out;
}

template <typename T>
bool operator==(const ArrayView<T> &lhs, const ArrayView<T> &rhs)
{
    if (lhs.size() != rhs.size()) {
        return false;
    }
    for (std::size_t i = 0; i < lhs.size(); ++i) {
        if (lhs[i] != rhs[i]) return false;
    }
    return true;
}

// ConstArrayView
template <typename T>
ConstArrayView<T>::ConstArrayView(std::size_t size, const T* data)
  : data_(data)
  , size_(size)
{}

// operators
template <typename T>
std::ostream &operator<<(std::ostream &out, const ConstArrayView<T> &a) {
    out << "[";
    bool is_first = true;
    for (const auto& v : a) {
        if (is_first) {
            is_first = false;
        } else {
            out << ", ";
        }
        out << v;
    }
    out << "]";
    return out;
}

template <typename T>
bool operator==(const ConstArrayView<T> &lhs, const ConstArrayView<T> &rhs)
{
    if (lhs.size() != rhs.size()) {
        return false;
    }
    for (std::size_t i = 0; i < lhs.size(); ++i) {
        if (lhs[i] != rhs[i]) return false;
    }
    return true;
}

} // namespace gwmath
