// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "gwLogger.h"

#include <fstream>
#include <string>

using namespace std;

std::unique_ptr<Logger> Logger::logger_instance = nullptr;

Logger& Logger::getLogger(const std::string& filename)
{
  if (!logger_instance) {
    if (filename == "stdout") {
      logger_instance = unique_ptr<Logger>(new Logger());
    } else {
      logger_instance = unique_ptr<Logger>(new Logger(filename)); //make_unique<Logger>(filename);
    }
  }
  return *logger_instance;
}

void Logger::deleteLogger()
{
    if (!logger_instance) {
        logger_instance = nullptr;
    }
}

Logger::Logger()
  : out_(cout)
{
}

Logger::Logger(const std::string& filename)
  : pout(make_unique<ofstream>(filename)), out_(*pout)
{
}


Logger& Logger::printDblMtrx(const std::vector<std::vector<double>>& mtrx, char sep)
{
    if (mtrx.size() == 0) return *this;

    size_t col_count = mtrx.size();
    size_t row_count = mtrx[0].size();
    for (size_t i = 0; i < row_count; ++i) {
        for (size_t j = 0; j < col_count; ++j) {
            out_ << mtrx[j].at(i);
            if (j+1 != col_count) {
                out_ << sep;
            }
        }
        out_ << '\n';
    }

    return *this;
}

void Logger::printEqual(const std::string& name, double value) {
    out_ << name << '=' << value << '\n';
}

void Logger::printEqualWithError(const std::string& name, double value, double dValue) {
    out_ << name << '=' << value << " +/- " << dValue << '\n';
}

void Logger::printEqualWithErrorRel(const std::string& name, double value, double dValue, double dValueRelative) {
    out_ << name << '=' << value << " +/- " << dValue << " (" << dValueRelative*100 << "%)\n";
}

