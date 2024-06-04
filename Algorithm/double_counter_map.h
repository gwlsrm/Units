#pragma once

#include <map>
#include <cmath>

#include "../Math/math_lib.h"

/**
 * @brief map double_value to counter within epsilon
 */
template <typename T>
class DoubleCounterMap {
public:
    explicit DoubleCounterMap(double epsilon)
        : epsilon_(epsilon)
    {}

    void add_value(double value); ///< inc counter in dict if value exists or add new value with cnt = 1
    void inc_value_cnt(double value, T cnt=1); ///< inc counter in dict of cnt if value exists or add new value with cnt=cnt
    const std::map<double, T>& getCounterDict() const { return dict_; } ///< get counter map
    void clear() { dict_.clear(); };


private:
    double epsilon_ = 0;
    std::map<double, T> dict_;

    bool approx_equal(double lhs, double rhs) const {
        return fabs(lhs - rhs) < epsilon_;
    }
};

template <typename T>
void DoubleCounterMap<T>::add_value(double value) {
    auto it = dict_.lower_bound(value);
    if (it == dict_.end()) {
        if (!dict_.empty()) {
            auto pit = prev(it);
            if (approx_equal(value, pit->first)) {
                ++pit->second;
                return;
            }
        }
        dict_.emplace(value, 1);
    } else if (approx_equal(value, it->first)) {
        ++it->second;
    } else if (it != dict_.begin() && approx_equal(value, prev(it)->first)) {
        auto pit = prev(it);
        ++pit->second;
    } else {
        dict_.emplace(value, 1);
    }
}

template <typename T>
void DoubleCounterMap<T>::inc_value_cnt(double value, T cnt) {
    auto it = dict_.lower_bound(value);
    if (it == dict_.end()) {
        if (!dict_.empty()) {
            auto pit = prev(it);
            if (approx_equal(value, pit->first)) {
                pit->second += cnt;
                return;
            }
        }
        dict_.emplace(value, cnt);
    } else if (approx_equal(value, it->first)) {
        it->second += cnt;
    } else if (it != dict_.begin() && approx_equal(value, prev(it)->first)) {
        auto pit = prev(it);
        pit->second += cnt;
    } else {
        dict_.emplace(value, cnt);
    }
}
