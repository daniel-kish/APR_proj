#include <iostream>
#include "matrix.h"
#include "lesystem.h"
#include <iomanip>
#include <chrono>

void random_vec(std::valarray<double>& v)
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    time_t now_c = std::chrono::system_clock::to_time_t(now);

    std::uniform_real_distribution<double> unif(-5.0, 5.0);
    std::default_random_engine re(now_c);
    for (auto& elem : v)
        elem = unif(re);
}

std::ostream& operator << (std::ostream& out, std::valarray<double>&& v)
{
    for (auto& elem : v)
        out << elem << std::endl;

    return out;
}

int main()
{
    using namespace std;
    using namespace chrono;

    cout << "God bless this undertaking and let it all be allright!" << endl;

    size_t N(150);
    Matrix A(N);
    A.randomize(-5.0, 5.0);
    A(0,0) = 0.0; A(5,5) = 0.0; A(110,110) = 0.0;

    std::valarray<double> B(N);
    random_vec(B);

    LESystem s(A,B);
    try {
        cout << fixed << setprecision(16) << (A*s.solve() - B).sum() << endl;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << endl;
    }

//    auto t0 = high_resolution_clock::now();
//    auto t1 = high_resolution_clock::now();
//    cout << duration_cast<microseconds>(t1-t0).count() << endl;

    return 0;
}
