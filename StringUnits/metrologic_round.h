#pragma once
#ifndef METROLOGIC_ROUND_H_INCLUDED
#define METROLOGIC_ROUND_H_INCLUDED

#include <string>

namespace gwstr {

std::string metrologic_round(double value, double dvalue); // rounds using error
std::string metrologic_round(double dvalue);

} // namespace gwstr

#endif // METROLOGIC_ROUND_H_INCLUDED
