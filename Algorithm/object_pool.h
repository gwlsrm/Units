#pragma once
#include <algorithm>
#include <queue>
#include <stdexcept>
#include <set>


template <class T>
class ObjectPool {
public:
    T* allocate();
    T* tryAllocate();

    void deallocate(T* object);

    ~ObjectPool();

private:
    std::queue<T*> free_;
    std::set<T*> allocated_;
};

template <typename T>
T* ObjectPool<T>::allocate() {
    if (free_.empty()) {
        free_.push(new T);
    }
    auto ret = free_.front();
    free_.pop();
    allocated_.insert(ret);
    return ret;
}

template <typename T>
T* ObjectPool<T>::tryAllocate() {
    if (free_.empty()) {
        return nullptr;
    }
    return allocate();
}

template <typename T>
void ObjectPool<T>::deallocate(T* object) {
    if (allocated_.find(object) == allocated_.end()) {
        throw std::invalid_argument("");
    }
    allocated_.erase(object);
    free_.push(object);
}

template <typename T>
ObjectPool<T>::~ObjectPool() {
    for (auto x : allocated_) {
        delete x;
    }
    while (!free_.empty()) {
        auto x = free_.front();
        free_.pop();
        delete x;
    }
}
