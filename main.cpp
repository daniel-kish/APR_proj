#include <iostream>
#include "matrix.h"
#include "lesystem.h"
#include <iomanip>
#include <chrono>
#include "myequation.h"
#include <cmath>
#include <nesystem.h>
#include <fstream>

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
    using namespace chrono;

    cout << "God bless this undertaking and let it all be allright!" << endl;

    MyEquation eq;
    NESystem<MyEquation> sys(eq);
    valarray<double> sol(0.1,17);

//    cout << 0 <<": " << sol[6] << endl;
    for (int i = 1; i <= 10000; i++)
    {
        sol = sys.solve(sol);
        eq.update(sol[1], sol[9], sol[3]);
        clog << i*0.001 << ' ' << sol[6] << endl;
    }



    return 0;
}
