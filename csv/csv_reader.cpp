#include "csv_reader.h"

#include "StringUnits/str_utils.h"


std::unordered_map<std::string, std::vector<std::string>> CsvReader::readColumns() {
    if (!has_header_) {
        throw std::invalid_argument("readColumns work only with files with header");
    }
    readHeader();
    std::vector<std::vector<std::string>> data(header_.size());
    for (auto line_opt = rawReadLine(); line_opt.has_value(); line_opt = rawReadLine()) {
        auto line = *line_opt;
        if (line.size() != header_.size()) {
            throw std::runtime_error("csv-file has different elements in row than in header");
        }
        for (size_t i = 0; i < line.size(); ++i) {
            data[i].push_back(line[i]);
        }
    }
    std::unordered_map<std::string, std::vector<std::string>> res;
    for (size_t i = 0; i < header_.size(); ++i) {
        res[header_[i]] = data[i];
    }
    return res;
}


std::optional<std::vector<std::string>> CsvReader::rawReadLine() {
    std::string line;
    if (std::getline(in_, line)) {
        return split_into_words(line, sep_);
    } else {
        return std::nullopt;
    }
}

void CsvReader::readHeader() {
    auto line = rawReadLine();
    if (line.has_value()) {
        header_ = *line;
    } else {
        throw std::runtime_error("There is no header in file");
    }
}
