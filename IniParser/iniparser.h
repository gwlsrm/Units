#pragma once
#ifndef INIPARSER_H_INCLUDED
#define INIPARSER_H_INCLUDED

#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <optional>
#include <string_view>

#include "StringUnits/str_utils.h"
#include "Algorithm/dictionary.h"


/**
    \brief Simple ini-file parser

    Simple reader of files type:
    # comment
    // comment
    [section_name]
    'name' = 'value'
*/
class IniParser {
public:
    // ctors -- readers
    /// ctor with filename
    explicit IniParser(const std::string& filename, char decimal_sep = '\0');
    /// ctor with stream
    explicit IniParser(std::istream& in, char decimal_sep = '\0');
    // geters and checkers
    /// check section in ini
    bool hasSection(const std::string& section_name) const;
    /// check key in readed file
    bool hasValue(const std::string& section_name, const std::string& key) const;
    /// get string value by it's name
    const std::string& getStringValue(const std::string& section_name, const std::string& key) const;
    const std::string& getStringValueDef(const std::string& section_name, const std::string& key, const std::string& defValue) const;
    /// get value (copy if string) by its name, returns option value
    template <typename T>
    std::optional<T> getOptValue(const std::string& section_name, const std::string& key) const;
    /// get value by section and param name, throws exceptions
    template <typename T>
    T getValue(const std::string& section_name, const std::string& key) const;
    /// get value by section and param name, returns defValue if doesn't exist
    template <typename T>
    T getValueDef(const std::string& section_name, const std::string& key, const T& defValue) const;
    /// update variable using value in ini-file
    template <typename T>
    void updateValueIfExists(const std::string& section_name, const std::string& key, T& value) const;
    // write ini to file
    void writeToFile(const std::string& filename) const;
    void writeToStream(std::ostream& out) const;
    // set value to ini-file
    template <typename T>
    void setValue(const std::string& section_name, const std::string& key, const T& value);
private:
    using Section = Dict<std::string, std::string>;
    Dict<std::string, Section> data_;
    const std::string empty_string_;

    // methods
    void readFromStream(std::istream& in, char decimal_sep);
    void writeSection(std::ostream& out, const std::string& section_name, const Section& section) const;
    // getters
    const Section* getSection(const std::string& section_name) const;
    const std::string& getStringValue(const Section& section, const std::string& key) const;
    std::optional<int> getIntValueOpt(const Section& section, const std::string& key) const;
    std::optional<bool> getBoolValueOpt(const Section& section, const std::string& key) const;
    std::optional<double> getDoubleValueOpt(const Section& section, const std::string& key) const;
    int getIntValue(const Section& section, const std::string& key) const;
    bool getBoolValue(const Section& section, const std::string& key) const;
    double getDoubleValue(const Section& section, const std::string& key) const;
    // writers and creators
    Section& createSectionIfNotExist(const std::string& section_name);
    void setStringValue(Section& section, const std::string& key, const std::string& value);
    void setIntValue(Section& section, const std::string& key, int value);
    void setBoolValue(Section& section, const std::string& key, bool value);
    void setDoubleValue(Section& section, const std::string& key, double value);
};


template <typename T>
std::optional<T> IniParser::getOptValue(const std::string& section_name, const std::string& key) const {
    auto section_ptr = getSection(section_name);
    if (section_ptr == nullptr) {
        return std::nullopt;
    }
    if constexpr (std::is_same_v<T, bool>) {
        return getBoolValueOpt(*section_ptr, key);
    } else if constexpr (std::is_integral_v<T>) {
        return getIntValueOpt(*section_ptr, key);
    } else if constexpr (std::is_floating_point_v<T>) {
        return getDoubleValueOpt(*section_ptr, key);
    }
    const auto& par_value = getStringValue(*section_ptr, key);
    if (par_value.empty()) return std::nullopt;
    std::stringstream ss;
    ss << par_value;
    T res;
    ss >> res;
    return res;
}

template <typename T>
T IniParser::getValue(const std::string& section_name, const std::string& key) const {
    const auto& section = data_.at(section_name);
    if constexpr (std::is_same_v<T, bool>) {
        return getBoolValue(section, key);
    } else if constexpr (std::is_integral_v<T>) {
        return getIntValue(section, key);
    } else if constexpr (std::is_floating_point_v<T>) {
        return getDoubleValue(section, key);
    }
    const auto& par_value = getStringValue(section, key);
    if (par_value.empty()) {
        throw std::invalid_argument("No parameter with name " + key + " in file or it has bad type");
    }
    std::stringstream ss;
    ss << par_value;
    T res;
    ss >> res;
    return res;
}

template <typename T>
T IniParser::getValueDef(const std::string& section_name, const std::string& key, const T& defValue) const {
    auto section_ptr = getSection(section_name);
    if (section_ptr == nullptr) {
        return defValue;
    }
    if constexpr (std::is_same_v<T, bool>) {
        auto opt = getBoolValueOpt(*section_ptr, key);
        return opt ? *opt : defValue;
    } else if constexpr (std::is_integral_v<T>) {
        auto opt = getIntValueOpt(*section_ptr, key);
        return opt ? *opt : defValue;
    } else if constexpr (std::is_floating_point_v<T>) {
        auto opt = getDoubleValueOpt(*section_ptr, key);
        return opt ? *opt : defValue;
    }
    const auto& par_value = getStringValue(*section_ptr, key);
    if (par_value.empty()) return defValue;
    std::stringstream ss;
    ss << par_value;
    T res;
    ss >> res;
    return res;
}

template <typename T>
void IniParser::updateValueIfExists(const std::string& section_name, const std::string& key, T& value) const {
    auto section_ptr = getSection(section_name);
    if (section_ptr == nullptr) {
        return;
    }
    if constexpr (std::is_same_v<T, bool>) {
        auto opt = getBoolValueOpt(*section_ptr, key);
        if (opt) {
            value = *opt;
        }
    } else if constexpr (std::is_integral_v<T>) {
        auto opt = getIntValueOpt(*section_ptr, key);
        if (opt) {
            value = *opt;
        }
    } else if constexpr (std::is_floating_point_v<T>) {
        auto opt = getDoubleValueOpt(*section_ptr, key);
        if (opt) {
            value = *opt;
        }
    } else {
        const auto& par_value = getStringValue(*section_ptr, key);
        if (par_value.empty()) return;
        std::stringstream ss;
        ss << par_value;
        ss >> value;
    }
}

template <typename T>
void IniParser::setValue(const std::string& section_name, const std::string& key, const T& value) {
    // create section if section doesn't exist
    auto& section = createSectionIfNotExist(section_name);
    // set value, select by type
    if constexpr (std::is_same_v<T, std::string>) {
        return setStringValue(section, key, value);
    } else if constexpr (std::is_same_v<T, bool>) {
        return setBoolValue(section, key, value);
    } else if constexpr (std::is_integral_v<T>) {
        return setIntValue(section, key, value);
    } else if constexpr (std::is_floating_point_v<T>) {
        return setDoubleValue(section, key, value);
    }
    // try to use stringstream to convert value to string
    std::stringstream ss;
    ss << value;
    setStringValue(section, key, ss.str());
}


#endif // INIPARSER_H_INCLUDED
