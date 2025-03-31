#include "cnfreader.h"

#include <fstream>
#include <stdexcept>


template <class charT, charT sep>
class punct_facet: public std::numpunct<charT> {
protected:
    charT do_decimal_point() const { return sep; }
};


CnfReader::CnfReader(const std::string& filename, std::string_view sep, char decimal_sep)
{
    std::ifstream in(filename);
    if (!in) {
        throw std::invalid_argument(filename + " doesn't exist");
    }

    readFromStream(in, sep, decimal_sep);
}

CnfReader::CnfReader(std::istream& in, std::string_view sep, char decimal_sep) {
    readFromStream(in, sep, decimal_sep);
}

void CnfReader::readFromStream(std::istream& in, std::string_view sep, char decimal_sep) {
    if (decimal_sep == ',') {
        in.imbue(std::locale(std::cout.getloc(), new punct_facet<char, ','>));
    } else if (decimal_sep != '\0') {
        in.imbue(std::locale(std::cout.getloc(), new punct_facet<char, '.'>));
    }
    for (std::string line; std::getline(in, line); ) {
        line = trim(line);
        if (line.empty() || line[0] == '#' || startWith(line, "//")) {continue;}
        std::string_view data{line};
        auto word = strip(readToken(data, sep));
        data = strip(data);
        if (word.empty() || data.empty()) { continue;}
        data_[std::string(word)] = data;
    }
}

bool CnfReader::hasValue(const std::string& par_name) const {
    return data_.count(par_name) > 0;
}

const std::string& CnfReader::getStringValue(const std::string& par_name) const
{
    if (data_.count(par_name)) {
        return data_.at(par_name);
    } else {
        return empty_string_;
    }
}

std::optional<int> CnfReader::getIntValueOpt(const std::string& par_name) const {
    const auto& par_value = getStringValue(par_name);
    if (par_value.empty()) return std::nullopt;
    int res;
    if (tryStrToInt(par_value, res)) {
        return res;
    } else {
        return std::nullopt;
    }
}

std::optional<bool> CnfReader::getBoolValueOpt(const std::string& par_name) const {
    const auto& par_value = getStringValue(par_name);
    if (par_value.empty()) return std::nullopt;
    if (par_value.find("true") != std::string::npos) {
        return true;
    } else if (par_value.find("false") != std::string::npos) {
        return false;
    } else {
        return std::nullopt;
    }
}

std::optional<double> CnfReader::getDoubleValueOpt(const std::string& par_name) const {
    const auto& par_value = getStringValue(par_name);
    if (par_value.empty()) return std::nullopt;
    double res;
    if (tryStrToFloat(par_value, res)) {
        return res;
    } else {
        return std::nullopt;
    }
}

int CnfReader::getIntValue(const std::string& par_name) const {
    try {
        const auto& par_value = data_.at(par_name);
        return stol(par_value);
    } catch (const std::exception&) {
        throw std::invalid_argument("No parameter with name " + par_name + " in file or it has bad type");
    }
}

bool CnfReader::getBoolValue(const std::string& par_name) const {
    try {
        const auto &par_value = data_.at(par_name);
        if (par_value.find("true") != std::string::npos) {
            return true;
        } else if (par_value.find("false") != std::string::npos) {
            return false;
        } else {
            throw std::out_of_range(par_name + " is not in cnf_file");
        }
    } catch (const std::exception&) {
        throw std::invalid_argument("No parameter with name " + par_name + " in file or it has bad type");
    }
}

double CnfReader::getDoubleValue(const std::string& par_name) const {
    try {
        const auto& par_value = data_.at(par_name);
        return stod(par_value);
    } catch (const std::exception&) {
        throw std::invalid_argument("No parameter with name " + par_name + " in file or it has bad type");
    }
}
