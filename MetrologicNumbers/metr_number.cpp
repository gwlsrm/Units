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
    : m_value(aValue), m_unc(aUnc)
{
    if (m_unc < 0) m_unc = -m_unc;
}

void MetrNumber::setRelUnc(double aUnc)
{
    m_unc = aUnc * m_value;
}

std::ostream& operator<< (std::ostream& os, const MetrNumber& m)
{
    os << m.m_value << " +/- " << m.m_unc;
    return os;
}

string MetrNumber::asString()
{
    return to_string(m_value) + " +/- " + to_string(m_unc);
}

MetrNumber operator+(const MetrNumber &lhs, const MetrNumber &rhs)
{
    double tval = lhs.m_value + rhs.m_value;
    double tunc = hypot(lhs.m_unc, rhs.m_unc);
    return MetrNumber(tval, tunc);
}

MetrNumber operator-(const MetrNumber &lhs, const MetrNumber &rhs)
{
    double tval = lhs.m_value - rhs.m_value;
    double tunc = hypot(lhs.m_unc, rhs.m_unc);
    return MetrNumber(tval, tunc);
}

MetrNumber operator*(const MetrNumber &lhs, const MetrNumber &rhs)
{
    double tval = lhs.m_value * rhs.m_value;
    double tunc = 0;
    if (tval != 0)
        tunc = tval * hypot(lhs.m_unc/lhs.m_value, rhs.m_unc/rhs.m_value);
    return MetrNumber(tval, tunc);
}

MetrNumber operator/(const MetrNumber &lhs, const MetrNumber &rhs)
{
    assert(rhs.m_value != 0 && "Division by zero");
    double tval = lhs.m_value / rhs.m_value;
    double tunc = 0;
    if (tval != 0)
        tunc = tval * hypot(lhs.m_unc/lhs.m_value, rhs.m_unc/rhs.m_value);
    return MetrNumber(tval, tunc);
}

MetrNumber MetrNumber::operator-() const
{
    return MetrNumber(-m_value, m_unc);
}

bool operator==(MetrNumber &m1, MetrNumber &m2)
{
    return fabs(m1.m_value - m2.m_value) <= hypot(m1.m_unc, m2.m_unc);
}

bool operator!=(MetrNumber &m1, MetrNumber &m2)
{
    return fabs(m1.m_value - m2.m_value) > hypot(m1.m_unc, m2.m_unc);
}

bool operator>(MetrNumber &m1, MetrNumber &m2)
{
    return (m1.m_value - m2.m_value) > hypot(m1.m_unc, m2.m_unc);
}

bool operator<(MetrNumber &m1, MetrNumber &m2)
{
    return (m2.m_value - m1.m_value) > hypot(m1.m_unc, m2.m_unc);
}

bool operator>=(MetrNumber &m1, MetrNumber &m2)
{
    return !(m1 < m2);
}

bool operator<=(MetrNumber &m1, MetrNumber &m2)
{
    return !(m1 > m2);
}
