#include "iniparser.h"

#include <fstream>
#include <stdexcept>


template <class charT, charT sep>
class punct_facet: public std::numpunct<charT> {
protected:
    charT do_decimal_point() const { return sep; }
};


IniParser::IniParser(const std::string& filename, char decimal_sep)
{
    std::ifstream in(filename);
    if (!in) {
        throw std::invalid_argument(filename + " doesn't exist");
    }

    readFromStream(in, decimal_sep);
}

IniParser::IniParser(std::istream& in, char decimal_sep) {
    readFromStream(in, decimal_sep);
}

void IniParser::readFromStream(std::istream& in, char decimal_sep) {
    if (decimal_sep == ',') {
        in.imbue(std::locale(std::cout.getloc(), new punct_facet<char, ','>));
    } else if (decimal_sep != '\0') {
        in.imbue(std::locale(std::cout.getloc(), new punct_facet<char, '.'>));
    }
    std::string current_section_name = "";
    for (std::string line; std::getline(in, line); ) {
        line = trim(line);
        if (line.empty() || line[0] == '#' || startWith(line, "//")) {continue;}

        std::string_view data{line};
        if (startWith(data, "[")) {
            // parse section name
            if (!endWith(data, "]")) {
                throw std::invalid_argument("wrong ini-file format in line: " + line);
            }
            data.remove_prefix(1);
            data.remove_suffix(1);
            current_section_name = data;
        } else {
            // parse section parameters
            auto word = strip(readToken(data, "="));
            data = strip(data);
            if (word.empty() || data.empty()) { continue;}
            data_[current_section_name][std::string(word)] = data;
        }
    }
}

bool IniParser::hasSection(const std::string& section_name) const {
    return data_.count(section_name) > 0;
}

bool IniParser::hasValue(const std::string& section_name, const std::string& key) const {
    if (auto it = data_.find(section_name); it != data_.end()) {
        return it->second.count(key) > 0;
    }
    return false;
}

const std::string& IniParser::getStringValue(const std::string& section_name, const std::string& key) const
{
    if (auto it = data_.find(section_name); it != data_.end()) {
        if (it->second.count(key)) {
            return it->second.at(key);
        }
    }
    return empty_string_;
}

const std::string& IniParser::getStringValue(const Section& section, const std::string& key) const
{
    if (section.count(key)) {
        return section.at(key);
    }
    return empty_string_;
}

const std::string& IniParser::getStringValueDef(const std::string& section_name, const std::string& key, const std::string& defValue) const {
    if (auto it = data_.find(section_name); it != data_.end()) {
        if (it->second.count(key)) {
            return it->second.at(key);
        }
    }
    return defValue;
}

const IniParser::Section* IniParser::getSection(const std::string& section_name) const {
    if (auto it = data_.find(section_name); it != data_.end()) {
        return &(it->second);
    }
    return nullptr;
}

std::optional<int> IniParser::getIntValueOpt(const Section& section, const std::string& key) const {
    const auto& par_value = getStringValue(section, key);
    if (par_value.empty()) return std::nullopt;
    int res;
    if (tryStrToInt(par_value, res)) {
        return res;
    } else {
        return std::nullopt;
    }
}

std::optional<bool> IniParser::getBoolValueOpt(const Section& section, const std::string& key) const {
    const auto& par_value = getStringValue(section, key);
    if (par_value.empty()) return std::nullopt;
    if (par_value.find("true") != std::string::npos) {
        return true;
    } else if (par_value.find("false") != std::string::npos) {
        return false;
    } else {
        return std::nullopt;
    }
}

std::optional<double> IniParser::getDoubleValueOpt(const Section& section, const std::string& key) const {
    const auto& par_value = getStringValue(section, key);
    if (par_value.empty()) return std::nullopt;
    double res;
    if (tryStrToFloat(par_value, res)) {
        return res;
    } else {
        return std::nullopt;
    }
}

int IniParser::getIntValue(const Section& section, const std::string& key) const {
    try {
        const auto& par_value = section.at(key);
        return stol(par_value);
    } catch (const std::exception&) {
        throw std::invalid_argument("No parameter with name " + key + " in file or it has bad type");
    }
}

bool IniParser::getBoolValue(const Section& section, const std::string& key) const {
    try {
        const auto &par_value = section.at(key);
        if (par_value.find("true") != std::string::npos) {
            return true;
        } else if (par_value.find("false") != std::string::npos) {
            return false;
        } else {
            throw std::out_of_range(key + " is not in cnf_file");
        }
    } catch (const std::exception&) {
        throw std::invalid_argument("No parameter with name " + key + " in file or it has bad type");
    }
}

double IniParser::getDoubleValue(const Section& section, const std::string& key) const {
    try {
        const auto& par_value = section.at(key);
        return stod(par_value);
    } catch (const std::exception&) {
        throw std::invalid_argument("No parameter with name " + key + " in file or it has bad type");
    }
}

void IniParser::writeToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) {
        throw std::invalid_argument("cannot open '" + filename + "' to write");
    }
    this->writeToStream(out);
}

void IniParser::writeToStream(std::ostream& out) const {
    // write sections
    for (const auto& [section_name, section] : data_) {
        this->writeSection(out, section_name, section);
    }
}

void IniParser::writeSection(std::ostream& out, const std::string& section_name, const Section& section) const {
    if (!section_name.empty()) {
        out << "[" << section_name << "]\n";
    }
    for (const auto& [key, value] : section) {
        out << key << '=' << section.at(key) << '\n';
    }
}

IniParser::Section& IniParser::createSectionIfNotExist(const std::string& section_name) {
    if (auto it = data_.find(section_name); it != data_.end()) {
        return it->second;
    }
    // new section
    return data_[section_name];
}

void IniParser::setStringValue(Section& section, const std::string& key, const std::string& value) {
    section[key] = value;
}

void IniParser::setIntValue(Section& section, const std::string& key, int value) {
    section[key] = std::to_string(value);
}

void IniParser::setBoolValue(Section& section, const std::string& key, bool value) {
    section[key] = value ? "true" : "false";
}

void IniParser::setDoubleValue(Section& section, const std::string& key, double value) {
    section[key] = std::to_string(value);
}
