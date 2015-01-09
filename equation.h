#ifndef EQUATION_H
#define EQUATION_H
#include <valarray>
#include "matrix.h"
#include <cmath>

class Equation
{
    size_t sz;

    double R1 = 1000.0;
    double R2 = 1000.0;

    // diode
    double R3 = 1000000.0;
    double R4 = 20.0;
    double C2 = 1.0E-12;
    double Is = 1.0E-12;
    double n = 1.0;
    double Vt = 0.026;
    // end diode

    double L = 0.001;
    double C1 = 1.0E-6;

    double E1 = 1.0;
    double E2 = 0.0;
    double T = 1.0E-4;

    double ILprev = 0.0;
    double IC1prev = 0.0;
    double IC2prev = 0.0;

    double t = 0.0;
    double Dt;
public:
    Equation(double _Dt, size_t _sz = 20): sz{_sz}, Dt{_Dt}
    {}
    std::valarray<double> operator() (const std::valarray<double> &) const;
    Matrix jacoby(const std::valarray<double> &) const;
    size_t dim() const {
        return sz;
    }
    void update(double _ILprev, double _IC1prev, double _IC2prev)
    {
        t += Dt;
        E2 = 10.0*sin(2.0*3.1415926535/T * t);
        ILprev = _ILprev;
        IC1prev = _IC1prev;
        IC2prev = _IC2prev;
    }
};

#endif // EQUATION_H
