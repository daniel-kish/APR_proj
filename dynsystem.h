#ifndef DYNSYSTEM_H
#define DYNSYSTEM_H
#include "myequation.h"

class DynSystem
{
    double m;
    double k;
    double f;

    // num
    double Dt;
    MyEquation eq;
public:
    DynSystem();
};

#endif // DYNSYSTEM_H
