#ifndef DLL_LOADER_H_INCLUDED
#define DLL_LOADER_H_INCLUDED

#include <stdexcept>
#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif // _WIN32
#include <string>

/**
    \brief Wrapper class to work with dll
    
    RAII-wrapper class to work with dll. Can operate in windows and linux
*/
class DllLoader {
public:
    // ctors and dtor
    /// open (load) dll by name and throws invalid_argument if fails
    explicit DllLoader(const std::string& dll_name);
    DllLoader(const DllLoader&) = delete;
    DllLoader(DllLoader&& other) {
        dll_handle = other.dll_handle;
        other.dll_handle = nullptr;
    }
    DllLoader& operator=(const DllLoader&) = delete;
    DllLoader& operator=(DllLoader&& other) {
        dll_handle = other.dll_handle;
        other.dll_handle = nullptr;
        return *this;
    }
    ~DllLoader();
    /// Loads function from dll, if there is no function, throws invalid_argument
    template <typename ProcType>
    ProcType loadFunction(const std::string& func_name) {
        ProcType func;
    #ifdef __linux
        func = (ProcType)dlsym(dll_handle, func_name.c_str());
    #else
        func = (ProcType)GetProcAddress((HINSTANCE)dll_handle, func_name.c_str());
    #endif
        if (!func) {
        #ifdef __linux
            throw std::invalid_argument("There is no " + func_name + " function");
        #else
            DWORD dllerror = GetLastError();
            throw std::invalid_argument("There is no " + func_name + " function. Error code is "
                                         + std::to_string(dllerror));
        #endif
        }
        return func;
    }
    /// Loads function from dll, if there is no function, returns nullptr
    template <typename ProcType>
    ProcType loadFunctionNoThrow(const std::string& func_name) {
    #ifdef __linux
        return (ProcType)dlsym(dll_handle, func_name.c_str());
    #else
        return (ProcType)GetProcAddress((HINSTANCE)dll_handle, func_name.c_str());
    #endif
    }
private:
    //void* dll_handle;
#ifdef _WIN32
    HINSTANCE  dll_handle;
#else
    void* dll_handle;
#endif // _WIN32
};



#endif // DLL_LOADER_H_INCLUDED
