#ifndef POLYNOM_H_INCLUDED
#define POLYNOM_H_INCLUDED

#include <vector>
#include "MathLib.h"

class Polynom {
public:
    Polynom(std::vector<double> data, int degree);
    int getDegree() const {return coeffs_.empty() ? 0 : coeffs_.size() - 1}
private:
    stv::vector<double> coeffs_;
};

#endif // POLYNOM_H_INCLUDED
