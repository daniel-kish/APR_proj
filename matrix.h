#ifndef MATRIX_H
#define MATRIX_H
#include <valarray>
#include <iostream>
#include <chrono>
#include <random>


class Matrix
{
    std::valarray<double> v;
    size_t nr_rows;
    size_t nr_cols;
public:
    Matrix(size_t rows);
    Matrix(size_t rows, size_t cols);
    // copy
    Matrix(const Matrix &) = default;
    Matrix & operator=(const Matrix &) = default;
    // move
    Matrix(Matrix&&) = default;
    Matrix & operator= (Matrix &&) = default;

    size_t rows() const
    {
        return nr_rows;
    }
    size_t cols() const
    {
        return nr_cols;
    }

    void randomize(double lowerBnd, double upperBnd)
    {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        time_t now_c = std::chrono::system_clock::to_time_t(now);

        std::uniform_real_distribution<double> unif(lowerBnd, upperBnd);
        std::default_random_engine re(now_c);
        for (auto& elem : v)
            elem = unif(re);
    }

    double operator()(size_t row, size_t col) const;
    double& operator()(size_t row, size_t col);
    Matrix operator + (const Matrix& rhs);
    Matrix operator - (const Matrix& rhs);
    std::valarray<double> operator *(const std::valarray<double> &rhs);
};

std::ostream& operator<<(std::ostream&, const Matrix&);


#endif // MATRIX_H
