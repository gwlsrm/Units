#ifndef CNFREADER_H_INCLUDED
#define CNFREADER_H_INCLUDED

#include <string>
#include <unordered_map>

/**
    \brief Simple config (ini)-file reader
    
    Simple reader of files type: 
    "# comment"
    'name' = 'value'
*/
class CnfReader {
public:
    /// ctor with filename
    explicit CnfReader(const std::string& filename);
    /// get value by it's name
    std::string getValue(const std::string& par_name) const;
private:
    std::unordered_map<std::string, std::string> data_;
};

#endif // CNFREADER_H_INCLUDED
