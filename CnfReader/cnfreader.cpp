#include "cnfreader.h"

#include <fstream>
#include <stdexcept>
#include "UStrUtils_gw.h"

using namespace std;

CnfReader::CnfReader(const std::string& filename)
{
    ifstream in(filename);
    if (!in) {
        throw invalid_argument(filename + " doesn't exist");
    }

    for (string line; getline(in, line); ) {
        line = trim(line);
        if (line.empty() || line[0] == '#') {continue;}
        // TODO: add tab and use another spliter
        auto words = split_into_words(line);
        if (words.size() >= 2) {
            string par_value = move(words[1]);
            for (size_t i = 2; i < words.size(); ++i) {
                par_value += " " + words[i];
            }
            data_[move(words[0])] = move(par_value);
        }
    }
}

std::string CnfReader::getValue(const std::string& par_name) const
{
    if (data_.count(par_name)) {
        return data_.at(par_name);
    } else {
        return "";
    }
}


