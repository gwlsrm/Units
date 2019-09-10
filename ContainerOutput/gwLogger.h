#ifndef GWLOGGER_H_INCLUDED
#define GWLOGGER_H_INCLUDED

#include <iostream>
#include <vector>
#include <memory>

/**
    \brief Singleton Logger
    
    Logger can log info to cout or file. 
    It can be obtained as one instance from any place of code
*/
class Logger {
public:
    /// get instance of Logger (singleton)
    static Logger& getLogger(const std::string& filename = "stdout");
    /// delete instance of logger
    static void deleteLogger();

    // public log methods
    /// log variable of any type that has << operator
    template <typename T>
    friend Logger& operator<<(Logger& l, const T& value) {
        l.out_ << value;
        return l;
    }
    /// logs vector with specified separator. Can ends line
    template <typename T>
    Logger& print_vector(const std::vector<T>& vec, char sep = '\t', bool isEndLine = true) {
        bool is_first = true;
        for (const auto& value : vec) {
            if (is_first) {
                is_first = false;
            } else {
                out_ << sep;
            }
            out_ << value;
        }
        if (isEndLine) {
            out_ << '\n';
        }
        return *this;
    }
    /// prints double matrix with specified separator
    Logger& printDblMtrx(const std::vector<std::vector<double>>& mtrx, char sep = '\t');
    /// prints 'name'='value' and end of line
    void printEqual(const std::string& name, double value);
    /// prints 'name'='value'+/-'dValue' and end of line
    void printEqualWithError(const std::string& name, double value, double dValue);
    /// prints 'name'='value'+/-'dValue' (relError*100)% and end of line
    void printEqualWithErrorRel(const std::string& name, double value, double dValue, double dValueRelative);
private:
    // fields
    std::unique_ptr<std::ostream> pout = nullptr;
    std::ostream& out_;
    static std::unique_ptr<Logger> logger_instance;
    // ctors
    Logger();                     // log to stdout
    Logger(const std::string& filename);
    Logger(std::ostream& out) : out_(out) {}
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};



#endif // GWLOGGER_H_INCLUDED
