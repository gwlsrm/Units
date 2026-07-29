#pragma once
#ifndef FILEUTILS_H_INCLUDED
#define FILEUTILS_H_INCLUDED

#include <string>
#include <tuple>
#include <vector>

namespace gwstr {

constexpr char OS_SEP =
#ifdef __linux__
    '/';
#else
    '\\';
#endif

inline char getOsSep() { return OS_SEP; }
/// add os separator (slash) to path if it does not end with it
std::string addOsSep(std::string path);

/// returns name of application for windows and linux
std::string getApplicationName([[maybe_unused]]int argc, [[maybe_unused]]char** argv);
/// check if file is exists
bool fileExists(const std::string& filePath);

/// extracts file path from full path
std::string extractFilePath(const std::string &fname);
/// extracts filename from full path
std::string extractFileName(const std::string& filename);
/// extracts filename extension
std::string extractFileExt(const std::string& filename);
/// extracts path and filename from full path
std::tuple<std::string, std::string> pathSplit(const std::string& filepath);
/// extracts path+filename and extension from full path
std::tuple<std::string, std::string> pathSplitExt(const std::string& filepath);
/// join path and filename to full path
std::string pathJoin(const std::string& path, const std::string& filename);

/// get parent directory if exist
std::string parentDirectory(const std::string& path);
// try to make basedir + filename
std::string expandFileNamesToRelBaseDir(const std::string& fileName, const std::string& baseDir);

/// returns end of file like in windows
inline std::string get_windows_eol() {
    return std::string{char(0x0D), char(0x0A)};
}

} // namespace gwstr

#endif // FILEUTILS_H_INCLUDED
