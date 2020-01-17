#pragma once

#include <mutex>
#include <utility>

/**
    @brief Synchronized is wrapper for synchronized access to value
    
    @example
    Synchronized<std::map<int,int>> dict;
    {   // to shrink critical section
        auto access = dict.getAccess();
        auto& value = access.ref_to_value;
        value[0] = 42;
    }
    dict.getAccess().ref_to_value[1] = 43;
*/
template <typename T>
class Synchronized {
public:
  explicit Synchronized(T initial = T())
    : value(std::move(initial)) {}

  template <typename U>
  struct Access {
    U& ref_to_value;
    std::lock_guard<std::mutex> guard;
  };

  Access<T> getAccess() {
    return {value, std::lock_guard(m)};
  }
  
  Access<const T> getAccess() const {
    return {value, std::lock_guard(m)};
  }

private:
  T value;
  mutable std::mutex m;
};
