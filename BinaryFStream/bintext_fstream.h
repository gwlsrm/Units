#ifndef BINTEXT_FSTREAM_H_INCLUDED
#define BINTEXT_FSTREAM_H_INCLUDED

#include <string>
#include <fstream>

class BinTxtIFStream {
public:
    explicit BinTxtIFStream(const std::string& filename);
    BinTxtIFStream(const BinTxtIFStream&) = delete;
    BinTxtIFStream& operator=(const BinTxtIFStream&) = delete;
    // methods
    bool is_open() {return m_stream.is_open();}
    BinTxtIFStream& getline(std::string& line, char sep = '\n');
    void ignore(uint32_t cnt);
    BinTxtIFStream& read_int(int& value);
    BinTxtIFStream& read_uint(uint32_t& value);
    BinTxtIFStream& getNameValue(std::string& name, std::string& value,
                                 const std::string& stop_name, char sep = '=');
    // operators
    operator bool();
private:
    std::ifstream m_stream;
};

bool getline(BinTxtIFStream& in, std::string& line, char sep = '\n');

#endif // BINTEXT_FSTREAM_H_INCLUDED
