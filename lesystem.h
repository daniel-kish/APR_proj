#ifndef LESYSTEM_H
#define LESYSTEM_H
#include "matrix.h"
#include <valarray>

class LESystem
{
    Matrix A;
    std::valarray<double> B;
public:
    LESystem();
    // restrict move and copy
    LESystem(const LESystem&) = delete;
    LESystem& operator=(const LESystem&) = delete;
    LESystem(LESystem&&) = delete;
    LESystem& operator=(LESystem&&) = delete;

    LESystem(const Matrix &, const std::valarray<double> &);   // work with copies
    LESystem(Matrix&&, std::valarray<double>&&);               // steal(move) and "spoil"
    LESystem(const Matrix &, std::valarray<double>&&);           // steal only free member
    LESystem(Matrix&&, const std::valarray<double> &);         // steal only Matrix

    std::valarray<double> solve();
    void print();
private:
    void gauss_fwd();
    std::valarray<double> gauss_bwd();
    void swap_rows(size_t i, size_t j);
    size_t safeRowBelow(size_t);
};

#endif // LESYSTEM_H
