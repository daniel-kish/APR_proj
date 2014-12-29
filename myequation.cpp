#include "myequation.h"

#include <assert.h>
#include <valarray>

#include "matrix.h"

std::valarray<double> MyEquation::operator() (const std::valarray<double> & arg) const
{
    assert(arg.size() == sz);
    std::valarray<double> v(sz);

        // topological eqs
    // voltages
    v[0] = arg[2] - arg[1];
    v[1] = arg[3] - arg[5];
    v[2] = arg[4] + arg[5];
    v[3] = arg[6] + arg[0] + arg[1] + arg[5];
    // currents
    v[4] = arg[7] - arg[9];
    v[5] = arg[8] + arg[9] - arg[13];
    v[6] = arg[12] + arg[10] - arg[11] - arg[13];

        // component eqs
    v[7] = arg[0] - E1;
    v[8] = arg[14] - arg[8]/C2;
    v[9] = arg[2] - L3*arg[15];
    v[10] = arg[16] - arg[10]/C4;
    v[11] = arg[11] - Is*(exp(arg[4] / (n*Vt)) - 1.0);
    v[12] = arg[5] - arg[12]*R6;
    v[13] = arg[6] - arg[13]*R7;

        // numeric eqs
    v[14] = arg[14] - (arg[1] - U2prev)/Dt;
    v[15] = arg[15] - (arg[9] - I3prev)/Dt;
    v[16] = arg[16] - (arg[3] - U4prev)/Dt;

    return v;
}

Matrix MyEquation::jacoby (const std::valarray<double> &arg) const
{
    assert(arg.size() == sz);

    Matrix J(sz);
    J(0,2) = 1.0; J(0,1) = -1.0;
    J(1,3) = 1.0; J(1,5) = -1.0;
    J(2,4) = 1.0; J(2,5) = 1.0;
    J(3,6) = 1.0; J(3,0) = 1.0; J(3,1) = 1.0; J(3,5) = 1.0;

    J(4,7) = 1.0; J(4,9) = -1.0;
    J(5,8) = 1.0; J(5,9) = 1.0; J(5,13) = -1.0;
    J(6,12) = 1.0; J(6,10) = 1.0; J(6,11) = -1.0; J(6,13) = -1.0;

    J(7,0) = 1.0;
    J(8,14) = 1.0; J(8,8) = -1.0/C2;
    J(9,2) = 1.0; J(9,15) = -L3;
    J(10,16) = 1.0; J(10,10) = -1.0/C4;
    J(11,11) = 1.0; J(11, 4) = -Is*exp(arg[4] / (n*Vt)) / (n*Vt);
    J(12,5) = 1.0; J(12, 12) = -R6;
    J(13,6) = 1.0; J(13, 13) = -R7;
    J(14,14) = 1.0; J(14,1) = -1.0/Dt;
    J(15, 15) = 1.0; J(15, 9) = -1.0/Dt;
    J(16,16) = 1.0; J(16,3) = -1.0/Dt;


    return J;
}
