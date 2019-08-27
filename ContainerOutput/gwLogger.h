#ifndef GWLOGGER_H_INCLUDED
#define GWLOGGER_H_INCLUDED

#include <iostream>
#include <vector>
#include <memory>

class Logger { // singleton
public:
    // get instance of Logger (singleton)
    static Logger& getLogger(const std::string& filename = "stdout");

    // public log methods
    template <typename T>
    friend Logger& operator<<(Logger& l, T value) {
        l.out_ << value;
        return l;
    }
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
    Logger& printDblMtrx(const std::vector<std::vector<double>>& mtrx, char sep = '\t');
    void printEqual(const std::string& name, double value);
    void printEqualWithError(const std::string& name, double value, double dValue);
    void printEqualWithErrorRel(const std::string& name, double value, double dValue, double dValueRelative);
private:
    // fields
    std::unique_ptr<std::ostream> pout = nullptr;
    std::ostream& out_;
    static std::unique_ptr<Logger> logger_instance;
    // ctors
    Logger();                             // log to stdout
    Logger(const std::string& filename);
    Logger(std::ostream& out) : out_(out) {}
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};



#endif // GWLOGGER_H_INCLUDED
