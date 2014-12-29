#ifndef EQUATION_H
#define EQUATION_H
#include <valarray>
#include "matrix.h"

class Equation
{
    size_t sz;

    double t = 0.0;
    double Dt;
public:
    MyEquation(double _Dt, size_t _sz = 20): sz{_sz}, Dt{_Dt}
    {}
    std::valarray<double> operator() (const std::valarray<double> &) const;
    Matrix jacoby(const std::valarray<double> &) const;
    size_t dim() const {
        return sz;
    }
    void update(double _U2prev, double _I3prev, double _U4prev)
    {
        t += Dt;
    }
};

#endif // EQUATION_H
