#include "dll_loader.h"

using namespace std;

DllLoader::DllLoader(const std::string& dll_name)
{
#ifdef __linux
    dll_handle = dlopen(dll_name.c_str(), RTLD_LAZY);
#else
    dll_handle = LoadLibraryA(dll_name.c_str());
#endif
    if (!dll_handle) {
    #ifdef __linux
        throw invalid_argument("Cannot load library " + dll_name + '\n' + dlerror());
    #else
        auto dlerror = GetLastError();
        throw invalid_argument("Cannot load library " + dll_name + ". Error code is " + to_string(dlerror));
    #endif
    }
}

DllLoader::~DllLoader()
{
    if (dll_handle) {
    #ifdef __linux
       dlclose(dll_handle);
    #else
       FreeLibrary((HINSTANCE)dll_handle);
    #endif
    }
}

std::optional<DllLoader> tryLoadDllFromNames(const std::vector<std::string>& dll_names) {
    for (const auto& dll_name : dll_names) {
        try {
            return DllLoader(dll_name);
        } catch (const invalid_argument&) {

        }
    }
    return std::nullopt;
}
