#ifndef FILEUTILS_H_INCLUDED
#define FILEUTILS_H_INCLUDED

#include <string>
#include <vector>

// file structure
std::string getApplicationName(int argc, char* argv[]);
std::string extractFilePath(const std::string &fname);      // extracts file path from full path
std::string extractFileName(const std::string& filename);   // extracts filename from full path
std::string extractFileExt(const std::string& filename);    // extracts filename extension
bool fileExists(const std::string& filePath); // check if file is exists
std::string expandFileNamesToRelBaseDir(const std::string& fileName, const std::string& baseDir);
std::string goOneLevelUp(const std::string& path);
std::string addSlash(std::string path);
inline char getSlash() {
#ifdef _WIN32
    return '\\';
#else
    return '/';
#endif
}
// save and load files
std::vector<std::string> loadStrListFromFile(const std::string& filename);
void saveStrListToFile(const std::vector<std::string>& str_list, std::string& filename);

//other
inline std::string get_windows_eol() {
    return std::string{char(0x0D), char(0x0A)};
}


#endif // FILEUTILS_H_INCLUDED
