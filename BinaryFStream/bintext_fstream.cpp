#include "bintext_fstream.h"
#include <fstream>


BinTxtIFStream::BinTxtIFStream(const std::string& filename)
{
    m_stream.open(filename, std::ios_base::binary);
}

BinTxtIFStream& BinTxtIFStream::getline(std::string& line, char sep)
{
    char c = '\0';
    line.clear();
    while(m_stream.get(c) && c != sep) {
        line += c;
    }
    return *this;
}

void BinTxtIFStream::ignore(std::uint32_t cnt)
{
    m_stream.ignore(cnt);
}

BinTxtIFStream& BinTxtIFStream::read_int(int& value)
{
    int sze = sizeof(value);
    m_stream.read((char*)&value, sze);
    return *this;
}

BinTxtIFStream& BinTxtIFStream::read_uint(std::uint32_t& value)
{
    int sze = sizeof(value);
    m_stream.read((char*)&value, sze);
    return *this;
}

BinTxtIFStream::operator bool()
{
    return static_cast<bool>(m_stream);
}

BinTxtIFStream& BinTxtIFStream::getNameValue(std::string& name, std::string& value,
                                 const std::string& stop_name, char sep)
{
    /** reading lines as "name=value"*/
    char c = '\0';
    // read name to sep
    name.clear();
    while(m_stream.get(c) && c != sep && c != '\n') {
        if (c != '\r')
            name += c;
    }
    // reading value
    value.clear();
    if (c == sep && name != stop_name) {
        while(m_stream.get(c) && c != '\n') {
            if (c != '\r')
                value += c;
        }
    }
    return *this;
}


bool getline(BinTxtIFStream& in, std::string& line, char sep) {
    return static_cast<bool>(in.getline(line, sep));
}
