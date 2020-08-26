#ifndef METRNUMBER_H
#define METRNUMBER_H

#include <string>

/**
    @brief class metrologic numbers: value and uncertainty
    
    Metrological numbers class: value and uncertainty. 
    Arithmetic operations for such numbers are realized
*/
class MetrNumber {
public:
    /// default constructor value = 0, unc = 0
    MetrNumber() = default;
    explicit MetrNumber(double aValue, double aUnc = 0);
    // getters and setters
    [[nodiscard]] double value() const {return value_;};
    void setValue(double aValue) { value_ = aValue;}
    [[nodiscard]] double unc() const {return unc_;};
    void setUnc(double aUnc) { unc_ = aUnc;};
    [[nodiscard]] double getRelUnc() const {return value_ != 0 ? unc_ / value_ : 0;}
    void setRelUnc(double aUnc);
    // representation
    std::string asString();
    friend std::ostream& operator<< (std::ostream& out, const MetrNumber& m);
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
    explicit operator bool() const {return value_ != 0;};
    friend bool operator==(const MetrNumber &lhs, const MetrNumber &rhs);
    friend bool operator!=(const MetrNumber &lhs, const MetrNumber &rhs);
    friend bool operator>(const MetrNumber &lhs, const MetrNumber &rhs);
    friend bool operator<(const MetrNumber &lhs, const MetrNumber &rhs);
    friend bool operator>=(const MetrNumber &lhs, const MetrNumber &rhs);
    friend bool operator<=(const MetrNumber &lhs, const MetrNumber &rhs);
private:
    double value_ = 0;
    double unc_ = 0;
};

#endif // METRNUMBER_H
