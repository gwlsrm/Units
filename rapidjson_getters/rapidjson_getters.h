#pragma once

#include "rapidjson/document.h"
#include <string_view>
#include <string>
#include <typeinfo>

namespace rapidjson {

inline const rapidjson::Value& get_value_or_except(const rapidjson::Value& node, std::string_view param_name) {
    auto it = node.FindMember(param_name.data());
    if (it == node.MemberEnd()) {
        throw std::invalid_argument(std::string("No param name: \"") 
            + std::string(param_name) + "\" in document");
    }
    return it->value;
}

template <typename T>
T read_value(const rapidjson::Value& node) {
    throw std::runtime_error(std::string("Unrealized type ") + typeid(T).name());
}

template <typename T>
bool is_correct_type(const rapidjson::Value& node) {
    throw std::runtime_error(std::string("Unrealized type ") + typeid(T).name());
}

template <typename T>
T get_or_except(const rapidjson::Value& node, std::string_view param_name) {
    const auto& new_value = get_value_or_except(node, param_name);
    if (!is_correct_type<T>(new_value)) {
        throw std::invalid_argument(std::string("Bad type for param name: \"")
            + std::string(param_name) + "\" in document");
    }
    return read_value<T>(new_value);
}

template <typename T>
T get_or_default(const rapidjson::Value& node, std::string_view param_name, const T& default_value) {
    auto it = node.FindMember(param_name.data());
    if (it == node.MemberEnd() || !is_correct_type<T>(it->value)) {
        return default_value;
    }
    return read_value<T>(it->value);
}

template <typename T>
void get_if_exists(const rapidjson::Value& node, std::string_view param_name, T& value) {
    auto it = node.FindMember(param_name.data());
    if (it != node.MemberEnd() && is_correct_type<T>(it->value)) {
        value = read_value<T>(it->value);
    }
}

template <>
inline double read_value<double>(const rapidjson::Value& node) {
    return node.GetDouble();
}

template <>
inline int read_value<int>(const rapidjson::Value& node) {
    return node.GetInt();
}

template <>
inline bool read_value<bool>(const rapidjson::Value& node) {
    return node.GetBool();
}

template <>
inline std::string read_value<std::string>(const rapidjson::Value& node) {
    return node.GetString();
}

template <>
inline bool is_correct_type<double>(const rapidjson::Value& node) {
    return node.IsNumber();
}

template <>
inline bool is_correct_type<int>(const rapidjson::Value& node) {
    return node.IsNumber();
}

template <>
inline bool is_correct_type<bool>(const rapidjson::Value& node) {
    return node.IsBool();
}

template <>
inline bool is_correct_type<std::string>(const rapidjson::Value& node) {
    return node.IsString();
}

inline auto get_value_as_array(const rapidjson::Value& node, std::string_view param_name) {
    const auto& array_node = get_value_or_except(node, param_name);
    if (!array_node.IsArray()) {
        throw std::invalid_argument(std::string("Expected key ") + std::string(param_name) + " is array");
    }
    return array_node.GetArray();
}

}
