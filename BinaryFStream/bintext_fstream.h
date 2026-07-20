#pragma once
#ifndef BINTEXT_FSTREAM_H_INCLUDED
#define BINTEXT_FSTREAM_H_INCLUDED

#include <cstdint>
#include <fstream>
#include <string>

/**
    \brief class is intended to work with text data in binary files

    Can read lines, read int values, read 'name'='value' strings
*/
class BinTxtIFStream {
public:
    /// constructs stream from filename
    explicit BinTxtIFStream(const std::string& filename);
    BinTxtIFStream(const BinTxtIFStream&) = delete;
    BinTxtIFStream& operator=(const BinTxtIFStream&) = delete;

    // methods
    /// is stream opened
    bool is_open() {return m_stream.is_open();}
    /// read line from stream (file) and stores it to line, end of line can be setted
    BinTxtIFStream& getline(std::string& line, char sep = '\n');
    /// ignore symbol
    void ignore(std::uint32_t cnt);

    /// read number stored in binare format
    template <typename T>
    BinTxtIFStream& read_number(T& value);

    BinTxtIFStream& getNameValue(std::string& name, std::string& value,
                                 const std::string& stop_name, char sep = '=');
    // operators
    operator bool();
private:
    std::ifstream m_stream;
};

/// read line from stream (file) and stores it to line, end of line can be setted
/// return true if in isn't empty
bool getline(BinTxtIFStream& in, std::string& line, char sep = '\n');


template <typename T>
BinTxtIFStream& BinTxtIFStream::read_number(T& value) {
    auto sze = sizeof(value);
    m_stream.read((char*)&value, sze);
    return *this;
}

#endif // BINTEXT_FSTREAM_H_INCLUDED
