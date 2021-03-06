#ifndef MYEQUATION_H
#define MYEQUATION_H
#include <valarray>
#include <matrix.h>

class MyEquation
{
    size_t sz;

    double E1 = sin(0.0); // depends on time
    double C2 = 50.0E-6;
    double L3 = 0.001;
    double R7 = 1000;

    double R6 = -1E6;
    double C4 = -1.0E-12;
    double Is = -1.0E-12;
    double n = 1.0;
    double Vt = -0.02585;

    double U2prev = 0.0;
    double I3prev = 0.0;
    double U4prev = 0.0;
    double t = 0.0;
    double Dt;
public:
    MyEquation(double _Dt, size_t _sz = 17): sz{_sz}, Dt{_Dt}
    {}
    std::valarray<double> operator() (const std::valarray<double> &) const;
    Matrix jacoby(const std::valarray<double> &) const;
    size_t dim() const {
        return sz;
    }
    void update(double _U2prev, double _I3prev, double _U4prev)
    {
        t += Dt;
        E1 = sin(2*3.1415926535/2.5 * t);
        U2prev = _U2prev;
        I3prev = _I3prev;
        U4prev = _U4prev;
    }
};

#endif // MYEQUATION_H
