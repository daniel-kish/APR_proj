#include <iostream>
#include "matrix.h"
#include "lesystem.h"
#include <iomanip>
#include <chrono>
#include "myequation.h"
#include <cmath>
#include <nesystem.h>
#include <fstream>
#include "equation.h"

std::ostream& operator << (std::ostream& out, std::valarray<double>&& v)
{
    out << std::fixed << std::setprecision(6);
    for (auto& elem : v)
        out << elem << std::endl;

    return out;
}

std::ostream& operator << (std::ostream& out, std::valarray<double>& v)
{
    out << std::fixed << std::setprecision(6);
    for (auto& elem : v)
        out << elem << std::endl;

    return out;
}


int main()
{
    using namespace std;
    cout << "God bless this undertaking and let it all be allright!" << endl;

    double Dt = 0.0001;
    double T = 10.0;
    MyEquation eq(Dt);


    NESystem<MyEquation> sys(eq);
    valarray<double> sol(1.0, eq.dim());

    ofstream file("out6.svd");
    for (int i = 1; i <= T/Dt; i++)
    {
        sol = sys.solve(sol);
        eq.update(sol[1], sol[9], sol[3]);
        file << i*Dt << ' ' << -sol[6] <<' ' << -sol[1] << endl;
    }

    return 0;
}
