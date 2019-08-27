#ifndef CNFREADER_H_INCLUDED
#define CNFREADER_H_INCLUDED

#include <string>
#include <unordered_map>

class CnfReader {
public:
    explicit CnfReader(const std::string& filename);
    std::string getValue(const std::string& par_name) const;
private:
    std::unordered_map<std::string, std::string> data_;
};

#endif // CNFREADER_H_INCLUDED
