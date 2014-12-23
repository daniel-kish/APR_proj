#include "matrix.h"
#include <assert.h>
#include <iomanip>

Matrix::Matrix(std::size_t rows) : v(rows*rows), nr_rows{rows}, nr_cols{rows}
{
}

Matrix::Matrix(std::size_t rows, std::size_t cols)
    : v(rows*cols), nr_rows{rows}, nr_cols{cols}
{ }

double Matrix::operator()(std::size_t row, std::size_t col) const
{
    assert(row < nr_rows || col < nr_cols);
    return v[row*nr_cols + col];
}

double & Matrix::operator()(std::size_t row, std::size_t col)
{
    assert(row < nr_rows || col < nr_cols);
    return v[row*nr_cols + col];
}

Matrix Matrix::operator +(const Matrix &rhs)
{
    assert(rhs.cols() == nr_cols && rhs.rows() == nr_rows);

    Matrix res(nr_cols, nr_rows);
    res.v = this->v + rhs.v;

    return res;
}

Matrix Matrix::operator -(const Matrix &rhs)
{
    assert(rhs.cols() == nr_cols && rhs.rows() == nr_rows);

    Matrix res(nr_cols, nr_rows);
    res.v = this->v - rhs.v;

    return res;
}

std::valarray<double> Matrix::operator *(const std::valarray<double>& rhs)
{
    using namespace std;
    assert(rhs.size() == nr_cols);

    valarray<double> res(rhs.size());

    double scp{0.0};
    for (size_t i = 0; i < nr_rows; i++) {
        scp = 0.0;
        for (size_t j = 0; j < nr_cols; j++)
            scp += v[i*nr_cols + j] * rhs[j];
        res[i] = scp;
    }

    return res;
}

std::ostream& operator<<(std::ostream& out, const Matrix& m)
{
    using namespace std;

    out << fixed << setprecision(4);
    for (size_t r = 0; r < m.rows(); r++) {
        for (size_t c = 0; c < m.cols(); c++)
            out << setw(8) << m(r,c) << ' ';
        out << endl;
    }

    return out;
}
