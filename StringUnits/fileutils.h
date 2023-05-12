#pragma once
#ifndef FILEUTILS_H_INCLUDED
#define FILEUTILS_H_INCLUDED

#include <string>
#include <vector>

// file structure
/// returns name of application for windows and linux
std::string getApplicationName([[maybe_unused]]int argc, [[maybe_unused]]char* argv[]);
/// extracts file path from full path
std::string extractFilePath(const std::string &fname);
/// extracts filename from full path
std::string extractFileName(const std::string& filename);
/// extracts filename extension
std::string extractFileExt(const std::string& filename);
/// check if file is exists
bool fileExists(const std::string& filePath);
std::string expandFileNamesToRelBaseDir(const std::string& fileName, const std::string& baseDir);
std::string goOneLevelUp(const std::string& path);
std::string addSlash(std::string path);
/// add slash for windows and linux
inline char getSlash() {
#ifndef __linux__
    return '\\';
#else
    return '/';
#endif
}
// save and load files
std::vector<std::string> loadStrListFromFile(const std::string& filename);
void saveStrListToFile(const std::vector<std::string>& str_list, const std::string& filename);

/// returns end of file like in windows
inline std::string get_windows_eol() {
    return std::string{char(0x0D), char(0x0A)};
}


#endif // FILEUTILS_H_INCLUDED
