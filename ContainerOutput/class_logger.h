#pragma once

#include <iostream>

class LogCtor {
public:
    virtual ~LogCtor() {
        std::cout << "Dtor" << std::endl;
    }
protected:
    LogCtor() {
        std::cout << "Default ctor" << std::endl;
    }

    LogCtor(const LogCtor& other) {
        std::cout << "Copy ctor" << std::endl;
    }

    LogCtor(LogCtor&& other) {
        std::cout << "Move ctor" << std::endl;
    }
    
    LogCtor& operator=(const LogCtor& other) {
        std::cout << "copy assignment" << std::endl;
        return *this;
    }
    
    LogCtor& operator=(LogCtor&& other) {
        std::cout << "move assignment" << std::endl;
        return *this;
    }
};
