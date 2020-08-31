// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "metr_number.h"

#include <cassert>
#include <cmath>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

MetrNumber::MetrNumber(double aValue, double aUnc)
    : value_(aValue), unc_(aUnc)
{
    if (unc_ < 0) unc_ = -unc_;
}

void MetrNumber::setRelUnc(double aUnc)
{
    unc_ = aUnc * value_;
}

std::ostream& operator<< (std::ostream& out, const MetrNumber& m)
{
    out << m.value_ << " +/- " << m.unc_;
    return out;
}

string MetrNumber::asString()
{
    return to_string(value_) + " +/- " + to_string(unc_);
}

MetrNumber operator+(const MetrNumber &lhs, const MetrNumber &rhs)
{
    double tval = lhs.value_ + rhs.value_;
    double tunc = hypot(lhs.unc_, rhs.unc_);
    return MetrNumber{tval, tunc};
}

MetrNumber operator-(const MetrNumber &lhs, const MetrNumber &rhs)
{
    double tval = lhs.value_ - rhs.value_;
    double tunc = hypot(lhs.unc_, rhs.unc_);
    return MetrNumber{tval, tunc};
}

MetrNumber operator*(const MetrNumber &lhs, const MetrNumber &rhs)
{
    double tval = lhs.value_ * rhs.value_;
    double tunc = 0;
    if (tval != 0)
        tunc = tval * hypot(lhs.unc_ / lhs.value_, rhs.unc_ / rhs.value_);
    return MetrNumber{tval, tunc};
}

MetrNumber operator/(const MetrNumber &lhs, const MetrNumber &rhs)
{
    assert(rhs.value_ != 0 && "Division by zero");
    double tval = lhs.value_ / rhs.value_;
    double tunc = 0;
    if (tval != 0)
        tunc = tval * hypot(lhs.unc_ / lhs.value_, rhs.unc_ / rhs.value_);
    return MetrNumber{tval, tunc};
}

MetrNumber MetrNumber::operator-() const
{
    return MetrNumber{-value_, unc_};
}

bool operator==(const MetrNumber &lhs, const MetrNumber &rhs)
{
    return (lhs.value_ - rhs.value_) * (lhs.value_ - rhs.value_) 
        <= lhs.unc_ * lhs.unc_ + rhs.unc_ * rhs.unc_;
}

bool MetrNumber::cmpWithK(const MetrNumber &lhs, const MetrNumber &rhs, double k)
{
    return (lhs.value_ - rhs.value_) * (lhs.value_ - rhs.value_) 
        <= k*k * (lhs.unc_ * lhs.unc_ + rhs.unc_ * rhs.unc_);
}

bool operator!=(const MetrNumber &lhs, const MetrNumber &rhs)
{
    return !(lhs == rhs);
}

bool operator>(const MetrNumber &lhs, const MetrNumber &rhs)
{
    return (lhs.value_ - rhs.value_) > hypot(lhs.unc_, rhs.unc_);
}

bool operator<(const MetrNumber &lhs, const MetrNumber &rhs)
{
    return (rhs.value_ - lhs.value_) > hypot(lhs.unc_, rhs.unc_);
}

bool operator>=(const MetrNumber &lhs, const MetrNumber &rhs)
{
    return !(lhs < rhs);
}

bool operator<=(const MetrNumber &lhs, const MetrNumber &rhs)
{
    return !(lhs > rhs);
}
