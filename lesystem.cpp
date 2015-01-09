#include "lesystem.h"
#include <iostream>
#include <exception>

LESystem::LESystem(const Matrix & m, const std::valarray<double> & v)
    : A(m), B(v)
{
//    std::clog << "LESystem(const Matrix&, const std::valarray<double>&)\n";
}

LESystem::LESystem(Matrix &&m, std::valarray<double> &&v)
    : A( std::move(m) ), B( std::move(v) )
{
//    std::clog << "LESystem(Matrix &&m, std::valarray<double> &&v)\n";
}

LESystem::LESystem(const Matrix &m, std::valarray<double> &&v)
    : A(m), B( std::move(v) )
{
//    std::clog << "LESystem(const Matrix &m, std::valarray<double> &&v)\n";
}

LESystem::LESystem(Matrix &&m, const std::valarray<double> & v)
    : A(std::move(m)), B(v)
{
//    std::clog << "LESystem(Matrix &&m, const std::valarray<double> & v)\n";
}

std::valarray<double> LESystem::solve()
{
    gauss_fwd();
    return gauss_bwd();
}

void LESystem::gauss_fwd()
{
    double factor;
    for (size_t keyRow = 0; keyRow < A.rows(); keyRow++)
    {
        if ( fabs(A(keyRow, keyRow)) < 10.0E-6 )
        {
            size_t safeRow = safeRowBelow(keyRow);
            if (safeRow >= A.rows())
                throw std::runtime_error("Gaussian elimination failed!");
            swap_rows(keyRow, safeRow);
        }
        for (size_t row = keyRow+1; row < A.rows(); row++) {
            if (fabs(A(row,keyRow)) > 10.0E-16) {
                factor = (-1.0)*A(row, keyRow)/A(keyRow, keyRow);
                for (size_t col = 0; col < A.cols(); col++)
                    A(row, col) += A(keyRow, col)*factor;
                B[row] += B[keyRow]*factor;
            }
        }
    }
}

std::valarray<double> LESystem::gauss_bwd()
{
    std::valarray<double> X(B.size());
    double sum{0.0};

    // backward iteration with sustitution
    for (int keyRow = A.rows()-1; keyRow >= 0; keyRow--)
    {
        sum = 0.0;
        for (int col = A.cols()-1; col > keyRow; col--) {
            sum += X[col] * A(keyRow, col);
        }
        X[keyRow] = (B[keyRow] - sum)/A(keyRow, keyRow);
    }

    return X;
}

void LESystem::swap_rows(size_t i, size_t j)
{
    for (size_t col = 0; col < A.cols(); col++)
        std::swap( A(i,col), A(j,col) );
    std::swap(B[i], B[j]);
}

size_t LESystem::safeRowBelow(size_t origin)
{
    for (size_t row = origin; row < A.rows(); row++)
        if ( fabs(A(row, origin)) > 10.0E-6 )
            return row;
    return A.cols()+1; // if row == A.rows() - error
}
