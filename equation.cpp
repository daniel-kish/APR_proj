#include "equation.h"

std::valarray<double> Equation::operator()(const std::valarray<double> &arg) const
{
    assert(arg.size() == sz);
    std::valarray<double> v(sz);

    v[0] = arg[0] - arg[16] - arg[17];
    v[1] = arg[1] - arg[18];
    v[2] = arg[2] - arg[19];
    v[3] = arg[3] + arg[19];
    v[4] = arg[4] + arg[15] + arg[16] + arg[17] + arg[18] + arg[19];
    v[5] = arg[5] - arg[14];
    v[6] = arg[6] + arg[10] - arg[14];
    v[7] = arg[7] + arg[10] - arg[14];
    v[8] = arg[8] + arg[11] - arg[14];
    v[9] = arg[9] + arg[12] - arg[13] - arg[14];
    v[10] = arg[10] - arg[0]*R1;
    v[11] = arg[11] - arg[1]*R2;
    v[12] = arg[12] - arg[2]*R3;
    v[13] = arg[13] - arg[3]*R4;
    v[14] = arg[14] - I; //////////////
    v[15] = arg[15] - E1; /////////////
    v[16] = arg[16] - E2; //////////////
    v[17] = arg[17] - (arg[7] - ILprev)*L/Dt;
    v[18] = arg[18] - (arg[8] - IC1prev)*C1/Dt;
    v[19] = arg[19] - (arg[9] - IC2prev)*C2/Dt;

    return v;
}

Matrix Equation::jacoby(const std::valarray<double> &) const
{
    assert(arg.size() == sz);

    Matrix j(sz);

    for (int i = 0; i < sz; i++)
        j(i,i) = 1.0;

    j(0,16) = -1.0; j(0,17) = -1.0;
    j(1,18) = -1.0;
    j(2,19) = -1.0;
    j(3,19) = 1.0;
    j(4,15) = 1.0;
    j(4,16) = 1.0; j(4,17) = 1.0; j(4,18) = 1.0; j(4,19) = 1.0;
    j(5,14) = -1.0;
    j(6,10) = 1.0;
    j(6,14) = -1.0;
    j(7,10) = 1.0; j(7,14) = -1.0;
    j(8,11) = 1.0; j(8,14) = -1.0;
    j(9,12) = 1.0; j(9,13) = -1.0; j(9,14) = -1.0;
    j(10,0) = -R1;
    j(11,1) = -R2;
    j(12,2) = -R3;
    j(13,3) = -R4;
    // empty
    j(17,7) = -L/Dt;
    j(18,8) = -C1/Dt;
    j(19,9) = -C2/Dt;
}
