#include "datetime.h"

#include <iomanip>
#include <sstream>

#include "gw_contract.h"

namespace gwdatetime {

DateTime parseDateTime(const std::string& str) {
    // check formmat YYYY-MM-DD HH:MM:SS
    Require(
        str.size() == 19 &&
        str[4] == '-' &&
        str[7] == '-' &&
        str[10] == ' ' &&
        str[13] == ':' &&
        str[16] == ':',
        "Invalid date-time format #1: " + str + ", expected format: YYYY-MM-DD HH:MM:SS"
    );
    for (int i = 0; i < 19; ++i) {
        if (i == 4 || i == 7 || i == 10 || i == 13 || i == 16) {
            continue;
        }
        Require(isdigit(str[i]), "Invalid date-time format #2: " + str + ", expected format: YYYY-MM-DD HH:MM:SS");
    }

    // parse
    const int year = stoi(str.substr(0, 4));
    const int month = stoi(str.substr(5, 2));
    const int day = stoi(str.substr(8, 2));
    const int hour = stoi(str.substr(11, 2));
    const int minute = stoi(str.substr(14, 2));
    const int second = stoi(str.substr(17, 2));

    std::tm tm{};
    std::istringstream input{str};
    input >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    if (input.fail() || hour > 23 || minute > 59 || second > 59) {
        throw std::runtime_error("Invalid date-time format #3: " + str + ", expected format: YYYY-MM-DD HH:MM:SS");
    }

    const std::time_t timestamp = ::timegm(&tm);
    return Clock::from_time_t(timestamp);
}

std::string toString(const DateTime& dt) {
    const auto whole_seconds =
        std::chrono::floor<std::chrono::seconds>(dt);
    const std::time_t timestamp = Clock::to_time_t(whole_seconds);

    std::tm tm{};
    if(::gmtime_r(&timestamp, &tm) == nullptr) {
        throw std::runtime_error("Failed to convert date_time (time_t to tr)");
    }

    std::ostringstream out;
    out << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return out.str();
}

} // namespace gwdatetime
