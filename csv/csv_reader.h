#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <optional>
#include <unordered_map>
#include <vector>


/// CsvReader -- simple csv reader, can read csv-file line by line or
///  as dict: column_name -> column as vector
class CsvReader{
public:
    explicit CsvReader(const std::string& filename, char sep = ',', bool has_header = true)
        : in_(filename), sep_(sep), has_header_(has_header)
    {}
    CsvReader(const CsvReader&) = delete;
    CsvReader& operator=(const CsvReader&) = delete;

    // try to read line as array of words, 1st line is a header,
    // if cannot read header -- throw exception
    std::optional<std::vector<std::string>> readLine();

    // read csv-file as dict: column_name -> column as vector
    std::unordered_map<std::string, std::vector<std::string>> readColumns();

private:
    std::optional<std::vector<std::string>> rawReadLine();

    void readHeader();

private:
    std::ifstream in_;
    char sep_ = ',';
    bool has_header_ = false;
    std::vector<std::string> header_;
};
