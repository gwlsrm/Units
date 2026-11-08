#pragma once

#include <chrono>
#include <string>

namespace gwdatetime
{

using Clock = std::chrono::system_clock;
using DateTime = Clock::time_point;

// parse date-time from string format: YYYY-MM-DD HH:MM:SS
DateTime parseDateTime(const std::string& str);
std::string toString(const DateTime& dt);



} // namespace gwdatetime
