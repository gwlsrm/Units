#include "rapidjson/document.h"
#include <string_view>
#include <string>
#include <typeinfo>

namespace rapidjson {

inline const rapidjson::Value& get_value_or_except(const rapidjson::Value& value, std::string_view param_name) {
    auto it = value.FindMember(param_name.data());
    if (it == value.MemberEnd()) {
        throw std::invalid_argument(std::string("No param name: \"") 
            + std::string(param_name) + "\" in document");
    }
    return it->value;
}

template <typename T>
T read_value(const rapidjson::Value& value) {
    throw std::runtime_error(std::string("Unrealized type ") + typeid(T).name());
}

template <typename T>
T get_or_except(const rapidjson::Value& value, std::string_view param_name) {
    const auto& new_value = get_value_or_except(value, param_name);
    return read_value<T>(new_value);
}

template <typename T>
T get_or_default(const rapidjson::Value& value, std::string_view param_name, const T& default_value) {
    auto it = value.FindMember(param_name.data());
    if (it == value.MemberEnd()) {
        return default_value;
    }
    return read_value<T>(it->value);
}

template <>
double read_value<double>(const rapidjson::Value& value) {
    return value.GetDouble();
}

template <>
int read_value<int>(const rapidjson::Value& value) {
    return value.GetInt();
}

template <>
bool read_value<bool>(const rapidjson::Value& value) {
    return value.GetBool();
}

template <>
std::string read_value<std::string>(const rapidjson::Value& value) {
    return value.GetString();
}

}
