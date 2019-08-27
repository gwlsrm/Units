#pragma once

#include <sstream>
#include <stdexcept>
#include <iostream>
#include <string>

#include "container_output.h"

//namespace ContainerOutputTypes {

//template <typename Collection>
//std::string Join(const Collection& c, char d) {
//  std::stringstream ss;
//  bool first = true;
//  for (const auto& i : c) {
//    if (!first) {
//      ss << d;
//    }
//    first = false;
//    ss << i;
//  }
//  return ss.str();
//}
//
//template <typename K, typename V, template <typename, typename> class Map>
//std::ostream& PrintMap(std::ostream& os, const Map<K, V>& m) {
//    os << "{";
//    bool first = true;
//    for (const auto& kv : m) {
//        if (!first) {
//            os << ", ";
//        }
//        first = false;
//        os << kv.first << ": " << kv.second;
//    }
//    return os << "}";
//}
//
//}
//
//template <typename K, typename V>
//std::ostream& operator << (std::ostream& out, const std::pair<K, V>& p) {
//    return out << '(' << p.first << ',' << p.second << ')';
//}
//
//template <typename T>
//std::ostream& operator << (std::ostream& out, const std::vector<T>& vi) {
//    return out << '[' << ContainerOutputTypes::Join(vi, ',') << ']';
//}
//
//template <class T>
//std::ostream& operator << (std::ostream& out, const std::set<T>& si) {
//    return out << '[' << ContainerOutputTypes::Join(si, ',') << ']';
//}
//
//template <typename K, typename V>
//std::ostream& operator << (std::ostream& out, const std::map<K, V>& m) {
//    return out << '{' << ContainerOutputTypes::Join(m, ',') << '}';
//}
//
//template <class K, class V>
//std::ostream& operator << (std::ostream& os, const std::unordered_map<K, V>& m) {
//  return TestRunnerPrivate::PrintMap(os, m);
//}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint = {}) {
  if (!(t == u)) {
    std::ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw std::runtime_error(os.str());
  }
}

inline void Assert(bool b, const std::string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const std::string& test_name) {
    try {
      func();
      std::cerr << test_name << " OK" << std::endl;
    } catch (std::exception& e) {
      ++fail_count;
      std::cerr << test_name << " fail: " << e.what() << std::endl;
    } catch (...) {
      ++fail_count;
      std::cerr << "Unknown exception caught" << std::endl;
    }
  }

  ~TestRunner() {
    std::cerr.flush();
    if (fail_count > 0) {
      std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
      exit(1);
    }
  }
private:
  int fail_count = 0;
};

#define ASSERT_EQUAL(x, y) {            	                \
  std::ostringstream __assert_equal_private_os;	            \
  __assert_equal_private_os << #x << " != " << #y << ", "   \
    << __FILE__ << ":" << __LINE__;     	                \
  AssertEqual(x, y, __assert_equal_private_os.str());       \
}

#define ASSERT(x) {                               \
  std::ostringstream __assert_private_os;         \
  __assert_private_os << #x << " is false, "      \
    << __FILE__ << ":" << __LINE__;               \
  Assert(x, __assert_private_os.str());           \
}

#define ASSERT_VALUE(x, a, b) {                         \
  std::ostringstream __assert_value_private_os;         \
  __assert_value_private_os << #x << " is false, "      \
    << a << " != " << b << ", "                         \
    << __FILE__ << ":" << __LINE__;                     \
  Assert(x, __assert_value_private_os.str());           \
}

#define RUN_TEST(tr, func) \
  tr.RunTest(func, #func)
