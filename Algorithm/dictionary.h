#pragma once

#include <list>
#include <unordered_map>
#include <utility>


/**
 * @brief Dict -- dictionary (unordered_map) which remembers the order of addition
 *
 * Dict has interface of unordered_map,
 * but if iterate through Dict, elements will be out in the order, they were added
 */
template <typename K, typename V>
class Dict {
public:
    using List = typename std::list<std::pair<K, V>>;
    using ListIterator = typename List::iterator;
    using ConstListIterator = typename List::const_iterator;
    using Map = typename std::unordered_map<K, ListIterator>;
public:
    // capacity
    bool empty() const;
    std::size_t size() const;
    // iterators
    ListIterator begin();
    ConstListIterator begin() const;
    ListIterator end();
    ConstListIterator end() const;
    // modifiers
    void clear();
    std::size_t erase(const K& key);
    // lookup
    V& at(const K& key);
    const V& at(const K& key) const;
    V get(const K& key, const V& default_value) const;
    V& operator[](const K& key);
    ListIterator find(const K& key);
    ConstListIterator find(const K& key) const;
    std::size_t count(const K& key) const;
    bool contains(const K& key) const;
private:
    // members
    Map dict_;
    List lst_;
};

template <typename K, typename V>
bool Dict<K,V>::empty() const {
    return dict_.empty();
}

template <typename K, typename V>
std::size_t Dict<K,V>::size() const {
    return dict_.size();
}

template <typename K, typename V>
typename Dict<K,V>::ListIterator Dict<K,V>::begin() {
    return lst_.begin();
}

template <typename K, typename V>
typename Dict<K,V>::ConstListIterator Dict<K,V>::begin() const {
    return lst_.cbegin();
}

template <typename K, typename V>
typename Dict<K,V>::ListIterator Dict<K,V>::end() {
    return lst_.end();
}

template <typename K, typename V>
typename Dict<K,V>::ConstListIterator Dict<K,V>::end() const {
    return lst_.cend();
}

template <typename K, typename V>
void Dict<K,V>::clear() {
    dict_.clear();
    lst_.clear();
}

template <typename K, typename V>
std::size_t Dict<K,V>::erase(const K& key) {
    if (auto it = dict_.find(key); it != dict_.end()) {
        auto lit = it->second;
        lst_.erase(lit);
        dict_.erase(it);
        return 1;
    }
    return 0;
}

template <typename K, typename V>
V& Dict<K,V>::at(const K& key) {
    auto it = dict_.at(key);
    return it->second;
}

template <typename K, typename V>
const V& Dict<K,V>::at(const K& key) const {
    auto it = dict_.at(key);
    return it->second;
}

template <typename K, typename V>
V Dict<K,V>::get(const K& key, const V& default_value) const {
    if (dict_.count(key) == 0) {
        return default_value;
    }
    return this->at(key);
}

template <typename K, typename V>
V& Dict<K,V>::operator[](const K& key) {
    if (dict_.count(key) == 0) {
        dict_[key] = lst_.insert(lst_.end(), std::pair{key, V{}});
    }
    return dict_[key]->second;
}

template <typename K, typename V>
typename Dict<K,V>::ListIterator Dict<K,V>::find(const K& key) {
    auto it = dict_.find(key);
    if (it == dict_.end()) {
        return lst_.end();
    }
    return it->second;
}

template <typename K, typename V>
typename Dict<K,V>::ConstListIterator Dict<K,V>::find(const K& key) const {
    auto it = dict_.find(key);
    if (it == dict_.cend()) {
        return lst_.cend();
    }
    return it->second;
}

template <typename K, typename V>
std::size_t Dict<K,V>::count(const K& key) const {
    return dict_.count(key);
}

template <typename K, typename V>
bool Dict<K,V>::contains(const K& key) const {
    return dict_.count(key) > 0;
}
