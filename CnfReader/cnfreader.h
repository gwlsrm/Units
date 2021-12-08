#pragma once
#ifndef CNFREADER_H_INCLUDED
#define CNFREADER_H_INCLUDED

#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <optional>
#include <string_view>

#include "StringUnits/str_utils.h"

/**
    \brief Simple config (ini)-file reader
    
    Simple reader of files type: 
    "# comment"
    'name' = 'value'
*/
class CnfReader {
public:
    /// ctor with filename
    explicit CnfReader(const std::string& filename, std::string_view sep);
    /// ctor with stream
    explicit CnfReader(std::istream& in, std::string_view sep);
    /// check key in readed file
    bool hasValue(const std::string& par_name) const;
    /// get string value by it's name
    const std::string& getStringValue(const std::string& par_name) const;
    /// get value (copy if string) by its name, returns option value
    template <typename T>
    std::optional<T> getOptValue(const std::string& par_name) const {
        if constexpr (std::is_same_v<T, bool>) {
            return getBoolValueOpt(par_name);
        } else if constexpr (std::is_integral_v<T>) {
            return getIntValueOpt(par_name);
        } else if constexpr (std::is_floating_point_v<T>) {
            return getDoubleValueOpt(par_name);
        }
        const auto& par_value = getStringValue(par_name);
        if (par_value.empty()) return std::nullopt;
        std::stringstream ss;
        ss << par_value;
        T res;
        ss >> res;
        return res;
    }
    /// get value, throws exceptions
    template <typename T>
    T getValue(const std::string& par_name) const {
        if constexpr (std::is_same_v<T, bool>) {
            return getBoolValue(par_name);
        } else if constexpr (std::is_integral_v<T>) {
            return getIntValue(par_name);
        } else if constexpr (std::is_floating_point_v<T>) {
            return getDoubleValue(par_name);
        }
        const auto& par_value = getStringValue(par_name);
        if (par_value.empty()) {
            throw std::invalid_argument("No parameter with name " + par_name + " in file or it has bad type");
        }
        std::stringstream ss;
        ss << par_value;
        T res;
        ss >> res;
        return res;
    }
    template <typename T>
    T getValueDef(const std::string& par_name, const T& defValue) const {
        if constexpr (std::is_same_v<T, bool>) {
            auto opt = getBoolValueOpt(par_name);
            return opt ? *opt : defValue;
        } else if constexpr (std::is_integral_v<T>) {
            auto opt = getIntValueOpt(par_name);
            return opt ? *opt : defValue;
        } else if constexpr (std::is_floating_point_v<T>) {
            auto opt = getDoubleValueOpt(par_name);
            return opt ? *opt : defValue;
        }
        const auto& par_value = getStringValue(par_name);
        if (par_value.empty()) return defValue;
        std::stringstream ss;
        ss << par_value;
        T res;
        ss >> res;
        return res;
    }
    template <typename T>
    void updateValueIfExists(const std::string& par_name, T& value) const {
        if constexpr (std::is_same_v<T, bool>) {
            auto opt = getBoolValueOpt(par_name);
            if (opt) {
                value = *opt;
            }
        } else if constexpr (std::is_integral_v<T>) {
            auto opt = getIntValueOpt(par_name);
            if (opt) {
                value = *opt;
            }
        } else if constexpr (std::is_floating_point_v<T>) {
            auto opt = getDoubleValueOpt(par_name);
            if (opt) {
                value = *opt;
            }
        } else {
            const auto& par_value = getStringValue(par_name);
            if (par_value.empty()) return;
            std::stringstream ss;
            ss << par_value;
            ss >> value;
        }
    }
private:
    std::unordered_map<std::string, std::string> data_;
    const std::string empty_string_;

    // methods
    void readFromStream(std::istream& in, std::string_view sep);
    // getters
    std::optional<int> getIntValueOpt(const std::string& par_name) const;
    std::optional<bool> getBoolValueOpt(const std::string& par_name) const;
    std::optional<double> getDoubleValueOpt(const std::string& par_name) const;
    int getIntValue(const std::string& par_name) const;
    bool getBoolValue(const std::string& par_name) const;
    double getDoubleValue(const std::string& par_name) const;
};

#endif // CNFREADER_H_INCLUDED
