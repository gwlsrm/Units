#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>


class CsvWriter {
public:
    explicit CsvWriter(std::ostream& out, char sep = ',')
        : out_(out), sep_(sep)
    {}

    explicit CsvWriter(const std::string& filename, char sep = ',', bool append = false) 
        : f_(filename, append ? std::ios_base::app : std::ios_base::out), out_(f_), sep_(sep)
    {}

    CsvWriter(const CsvWriter&) = delete;
    CsvWriter& operator=(const CsvWriter&) = delete;

    template <typename T>
    CsvWriter& operator<<(const T& value) {
        addSepIfNeeded();
        out_ << value;
        return *this;
    }

    template <typename T>
    void writeLine(const std::vector<T>& sequence, bool is_end_line=false) {
        for (const auto& value : sequence) {
            this->operator<<(value);
        }
        if (is_end_line) {
            endLine();
        }
    }

    void endLine() {
        out_ << '\n';
        is_start_line_ = true;
    }

private:
    void addSepIfNeeded() {
        if (is_start_line_) {
            is_start_line_ = false;
        } else {
            out_ << sep_;
        }
    }

private:
    std::ofstream f_;
    std::ostream& out_;
    char sep_;
    bool is_start_line_ = true;
};

template <>
CsvWriter& CsvWriter::operator<<<std::string>(const std::string& value) {
    addSepIfNeeded();
    out_ << '"' << value << '"';
    return *this;
}

template <>
CsvWriter& CsvWriter::operator<<<std::string_view>(const std::string_view& value) {
    addSepIfNeeded();
    out_ << '"' << value << '"';
    return *this;
}
