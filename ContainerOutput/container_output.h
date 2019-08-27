#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <sstream>
#include <utility>
#include <string>
#include <set>

namespace ContainerOutputTypes {

template <typename Collection>
std::string Join(const Collection& c, char d) {
  std::stringstream ss;
  bool first = true;
  for (const auto& i : c) {
    if (!first) {
      ss << d;
    }
    first = false;
    ss << i;
  }
  return ss.str();
}

template <typename K, typename V, template <typename, typename> class Map>
std::ostream& PrintMap(std::ostream& os, const Map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

}

template <typename K, typename V>
std::ostream& operator << (std::ostream& out, const std::pair<K, V>& p) {
    return out << '(' << p.first << ',' << p.second << ')';
}

template <typename T>
std::ostream& operator << (std::ostream& out, const std::vector<T>& vi) {
    return out << '[' << ContainerOutputTypes::Join(vi, ',') << ']';
}

template <class T>
std::ostream& operator << (std::ostream& out, const std::set<T>& si) {
    return out << '[' << ContainerOutputTypes::Join(si, ',') << ']';
}

template <typename K, typename V>
std::ostream& operator << (std::ostream& out, const std::map<K, V>& m) {
    return out << '{' << ContainerOutputTypes::Join(m, ',') << '}';
}

template <class K, class V>
std::ostream& operator << (std::ostream& os, const std::unordered_map<K, V>& m) {
  return ContainerOutputTypes::PrintMap(os, m);
}

