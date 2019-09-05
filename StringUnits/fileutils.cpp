// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "fileutils.h"

#include <fstream>
#ifdef __WIN32
#include <windows.h>
#endif

using namespace std;

std::string getApplicationName(int argc, char* argv[]) {
#ifdef _WIN32
    char newPath[MAX_PATH];
    GetModuleFileNameA(0, newPath, MAX_PATH);
    return newPath;
#else
    return argv[0];
#endif

}

std::string extractFilePath(const std::string &fname)
{
    auto pos = fname.rfind('\\');
    if (pos == 0 || pos == fname.npos) {
        pos = fname.rfind('/');
        if (pos == 0 || pos == fname.npos)
            return fname;
    }

  return fname.substr(0, pos+1);
}

std::string extractFileName(const std::string& filename) {
    size_t pos = filename.rfind('\\');
    if (pos == 0 || pos == filename.npos) {
        pos = filename.rfind('/');
        if (pos == 0 || pos == filename.npos)
            return filename;
    }
    if (pos != filename.size()-1) {
        return filename.substr(pos+1);
    } else {
        return "";
    }
}

std::string extractFileExt(const std::string& filename) {
    size_t pos = filename.rfind('.');
    if (pos == 0 || pos == filename.npos) return "";

    return filename.substr(pos);
}

bool fileExists(const std::string& filePath) {
    ifstream fin(filePath.c_str());
    return fin.is_open();
}

std::string goOneLevelUp(const std::string& path) {
    if (path.empty()) {
        return path;
    }
    // only one /
    if (path.find('\\')+1 == path.size() || path.find('/')+1 == path.size()) {
        return path;
    }
    // remove last /
    string res(path);
    if (res.back() == '\\' || res.back() == '/') {
        res.pop_back();
    }

    // remove last level
    res = res.substr(0, res.rfind('\\') + 1);
    return res;
}

std::string addSlash(std::string path) {
    if (path.empty() || path.back() == '\\' || path.back() == '/') {
        return path;
    }
#ifdef _WIN32
    return path + '\\';
#else
    return path + '/';
#endif

}

std::string expandFileNamesToRelBaseDir(const std::string& fileName, const std::string& baseDir) {
    // absolute path
    if (fileName.find(':') != fileName.npos) {
        return fileName;
    }
    string res_path = addSlash(baseDir);
    // expand ..
    if (fileName.size() >= 3 && fileName.compare(0, 3, "..\\") == 0) {
        res_path = goOneLevelUp(res_path);
        res_path += fileName.substr(3);
    } else {
        res_path += fileName;
    }
    return res_path;
}

std::vector<std::string> loadListFromFile(const std::string& filename) {
    ifstream in;
    if (!in) {
        throw invalid_argument("Can't open file " + filename);
    }
    vector<string> res;
    string s;
    while (getline(in, s)) {
        res.push_back(move(s));
    }
    return res;
}

void saveStrListToFile(const std::vector<std::string>& str_list, const std::string& filename) {
    ofstream out;
    if (!out) {
        throw invalid_argument("Can't create file " + filename);
    }
    for (const auto& line : str_list) {
        out << line << '\n';
    }
}
