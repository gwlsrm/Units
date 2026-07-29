#include "fileutils.h"

#include <fstream>
#ifndef __linux__
#include <windows.h>
#endif

namespace gwstr {

std::string addOsSep(std::string path) {
    if (path.empty() || path.back() == OS_SEP) {
        return path;
    }
    return path + OS_SEP;
}

std::string getApplicationName([[maybe_unused]]int argc, [[maybe_unused]]char** argv) {
#ifndef __linux__
    char newPath[MAX_PATH];
    GetModuleFileNameA(0, newPath, MAX_PATH);
    return newPath;
#else
    return argv[0];
#endif
}

bool fileExists(const std::string& filePath) {
    std::ifstream fin(filePath.c_str());
    return fin.is_open();
}


std::string extractFilePath(const std::string &fname)
{
    auto pos = fname.rfind(OS_SEP);
    if (pos == 0 || pos == fname.npos) {
        return fname;
    }

  return fname.substr(0, pos+1);
}

std::string extractFileName(const std::string& filename) {
    size_t pos = filename.rfind(OS_SEP);
    if (pos == 0 || pos == filename.npos) {
        return filename;
    }
    if (pos != filename.size()-1) {
        return filename.substr(pos+1);
    } else {
        return "";
    }
}

std::string extractFileExt(const std::string& filename) {
    auto fname = extractFileName(filename);
    size_t pos = fname.rfind('.');
    if (pos == 0 || pos == fname.npos) return "";

    return fname.substr(pos);
}

std::tuple<std::string, std::string> pathSplit(const std::string& filepath) {
    auto pos = filepath.rfind(OS_SEP);
    if (pos == 0 || pos == filepath.npos) {
        return std::make_tuple("", filepath);
    }

    return std::make_tuple(filepath.substr(0, pos+1), filepath.substr(pos+1));
}

std::tuple<std::string, std::string> pathSplitExt(const std::string& filepath) {
    auto pos = filepath.rfind('.');
    if (pos == 0 || pos == filepath.npos) {
        return std::make_tuple(filepath, "");
    }

    return std::make_tuple(filepath.substr(0, pos), filepath.substr(pos));
}

std::string pathJoin(const std::string& path, const std::string& filename) {
    std::string res = path;
    if (res.back() != OS_SEP) {
        res += OS_SEP;
    }
    res += filename;
    return res;
}

std::string parentDirectory(const std::string& path) {
    if (path.empty()) {
        return path;
    }
    // only one /
    size_t slash_pos = path.find(OS_SEP);
    if (slash_pos == std::string::npos || slash_pos + 1 == path.size()) {
        return path;
    }

    // remove last /
    std::string res(path);
    if (res.back() == OS_SEP) {
        res.pop_back();
    }

    // remove last level
    slash_pos = res.rfind(OS_SEP);
    if (slash_pos != std::string::npos) {
        res.resize(slash_pos + 1);
    }
    return res;
}

std::string expandFileNamesToRelBaseDir(const std::string& fileName, const std::string& baseDir) {
    // absolute path
    if (fileName.find(':') != fileName.npos) {
        return fileName;
    }
    std::string res_path = addOsSep(baseDir);
    // expand ..
    if (fileName.size() >= 3 &&
        (fileName.compare(0, 3, "..\\") == 0  ||
        fileName.compare(0, 3, "../") == 0 )) {
        res_path = parentDirectory(res_path);
        res_path += fileName.substr(3);
    } else {
        res_path += fileName;
    }
    return res_path;
}

} // namespace gwstr
