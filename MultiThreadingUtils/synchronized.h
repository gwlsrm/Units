#pragma once

#include <mutex>
using namespace std;

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
    : value(move(initial))
  {
  }

  struct Access {
    T& ref_to_value;
    lock_guard<mutex> guard;
  };

  Access getAccess() {
    return {value, lock_guard(m)};
  }

private:
  T value;
  mutex m;
};



