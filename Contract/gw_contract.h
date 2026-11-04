#pragma once

#include <string>
#include <stdexcept>

inline void Require(bool condition, const std::string& message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}
