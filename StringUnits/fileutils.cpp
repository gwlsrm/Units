#include "fileutils.h"

#include <fstream>
#ifndef __linux__
#include <windows.h>
#endif


std::string getApplicationName([[maybe_unused]]int argc, [[maybe_unused]]char** argv) {
#ifndef __linux__
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
    std::ifstream fin(filePath.c_str());
    return fin.is_open();
}

std::string goOneLevelUp(const std::string& path) {
    if (path.empty()) {
        return path;
    }
    // only one /
    size_t slash_pos = path.find('\\');
    if (slash_pos == std::string::npos) {
        slash_pos = path.find('/');
    }
    if (slash_pos == std::string::npos || slash_pos + 1 == path.size()) {
        return path;
    }

    // remove last /
    std::string res(path);
    if (res.back() == '\\' || res.back() == '/') {
        res.pop_back();
    }

    // remove last level
    slash_pos = res.rfind('\\');
    if (slash_pos == std::string::npos) {
        slash_pos = res.rfind('/');
    }
    if (slash_pos != std::string::npos) {
        res.resize(slash_pos + 1);
    }
    return res;
}

std::string addSlash(std::string path) {
    if (path.empty() || path.back() == '\\' || path.back() == '/') {
        return path;
    }
#ifndef __linux__
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
    std::string res_path = addSlash(baseDir);
    // expand ..
    if (fileName.size() >= 3 &&
        (fileName.compare(0, 3, "..\\") == 0  ||
        fileName.compare(0, 3, "../") == 0 )) {
        res_path = goOneLevelUp(res_path);
        res_path += fileName.substr(3);
    } else {
        res_path += fileName;
    }
    return res_path;
}

std::vector<std::string> loadListFromFile(const std::string& filename) {
    std::ifstream in;
    if (!in) {
        throw std::invalid_argument("Can't open file " + filename);
    }
    std::vector<std::string> res;
    std::string s;
    while (std::getline(in, s)) {
        res.push_back(move(s));
    }
    return res;
}

void saveStrListToFile(const std::vector<std::string>& str_list, const std::string& filename) {
    std::ofstream out;
    if (!out) {
        throw std::invalid_argument("Can't create file " + filename);
    }
    for (const auto& line : str_list) {
        out << line << '\n';
    }
}
