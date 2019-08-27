#ifndef METRNUMBER_H
#define METRNUMBER_H

#include <string>

class MetrNumber {
public:
    MetrNumber() = default;
    MetrNumber(double aValue, double aUnc = 0);
    // getters and setters
    double getValue() const {return m_value;};
    void setValue(double aValue) {m_value = aValue;}
    double getUnc() const {return m_unc;};
    void setUnc(double aUnc) {m_unc = aUnc;};
    double getRelUnc() const {return m_value != 0 ? m_unc/m_value : 0;}
    void setRelUnc(double aUnc);
    // representation
    std::string asString();
    friend std::ostream& operator<< (std::ostream& os, const MetrNumber& m);
    std::string getValueAsString();
    std::string getUncAsString();
    std::string getRelUncAsString();
    // arithmetic operators
    friend MetrNumber operator+(const MetrNumber &lhs, const MetrNumber &rhs);
    friend MetrNumber operator-(const MetrNumber &lhs, const MetrNumber &rhs);
    friend MetrNumber operator*(const MetrNumber &lhs, const MetrNumber &rhs);
    friend MetrNumber operator/(const MetrNumber &lhs, const MetrNumber &rhs);
    // arithmetic unary operators
    MetrNumber operator-() const;
    // boolean operators
    operator bool() {return m_value != 0;};
    friend bool operator==(MetrNumber &m1, MetrNumber &m2);
    friend bool operator!=(MetrNumber &m1, MetrNumber &m2);
    friend bool operator>(MetrNumber &m1, MetrNumber &m2);
    friend bool operator<(MetrNumber &m1, MetrNumber &m2);
    friend bool operator>=(MetrNumber &m1, MetrNumber &m2);
    friend bool operator<=(MetrNumber &m1, MetrNumber &m2);
private:
    double m_value = 0;
    double m_unc = 0;
};

#endif // METRNUMBER_H
