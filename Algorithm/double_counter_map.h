#pragma once

#include <map>
#include <cmath>

#include "../Math/math_lib.h"

/**
 * @brief map double_value to counter within epsilon
 * 
 */
template <typename T>
class DoubleCounterMap {
public:
    explicit DoubleCounterMap(double epsilon)
        : epsilon_(epsilon) 
    {
        //TODO: constexpr int-type
    }

    void add_value(double value); ///< inc counter in dict if value exist or add new value with cnt = 1
    const std::map<double, T>& getCounterDict() const { return dict_; } ///< get counter map


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