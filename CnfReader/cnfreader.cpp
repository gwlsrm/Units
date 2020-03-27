#include "cnfreader.h"

#include <fstream>
#include <stdexcept>

using namespace std;

CnfReader::CnfReader(const std::string& filename, std::string_view sep)
{
    ifstream in(filename);
    if (!in) {
        throw invalid_argument(filename + " doesn't exist");
    }

    readFromStream(in, sep);
}

CnfReader::CnfReader(std::istream& in, std::string_view sep) {
    readFromStream(in, sep);
}

void CnfReader::readFromStream(std::istream& in, std::string_view sep) {
    for (string line; getline(in, line); ) {
        line = trim(line);
        if (line.empty() || line[0] == '#') {continue;}
        string_view data{line};
        auto word = strip(readToken(data, sep));
        data = strip(data);
        if (word.empty() || data.empty()) { continue;}
        data_[string(word)] = data;
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
    const auto& par_value = data_.at(par_name);
    return stol(par_value);
}

bool CnfReader::getBoolValue(const std::string& par_name) const {
    const auto& par_value = data_.at(par_name);
    if (par_value.find("true") != std::string::npos) {
        return true;
    } else if (par_value.find("false") != std::string::npos) {
        return false;
    } else {
        throw out_of_range(par_name + " is not in cnf_file");
    }
}

double CnfReader::getDoubleValue(const std::string& par_name) const {
    const auto& par_value = data_.at(par_name);
    return stod(par_value);
}


