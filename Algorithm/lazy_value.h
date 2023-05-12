#pragma once
#include <functional>
#include <optional>

template <typename T>
class LazyValue {
public:
  explicit LazyValue(std::function<T()> init) : init_(std::move(init)) {
  }

  bool hasValue() const {
    return value_.has_value();
  }

  const T& get() const {
    if (!value_) {
      value_ = init_();
    }
    return *value_;
  }

private:
  std::function<T()> init_;
  mutable std::optional<T> value_;
};
