#ifndef NESYSTEM_H
#define NESYSTEM_H
#include <valarray>
#include "lesystem.h"
#include <iostream>
#include <random>
#include <assert.h>

std::valarray<double> getRandomVec(size_t sz, double low=-5.0, double upper=5.0);


template <class Function>
// Function-related invariants:
// std::valarray<double> Function::operator(const std::valarray<double>&)
// Matrix Function::jacoby(const std::valarray<double>&)
// size_t Function::dim();
class NESystem
{
    const Function & fun;
    const int maxIter;
public:
    NESystem() = delete;
    NESystem(const Function& _F) : fun(_F), maxIter(150)
    { }
    std::valarray<double> solve(const std::valarray<double> & origin);
};

template <class Function>
std::valarray<double> NESystem<Function>::solve(const std::valarray<double> &origin)
{
    assert(origin.size() == fun.dim());
    using namespace std;

    // we will agressively spoil the origin's value so copy:
    std::valarray<double> appr(origin);
    int iterCount;
    for (iterCount = 1; iterCount <= maxIter; iterCount++) {
        LESystem s( fun.jacoby(appr), -fun(appr) );
        try {
            appr += s.solve();
        }
        catch (std::exception& e)
        {
//            std::cerr << e.what() << endl;
//            std::cerr << "But we will most certainly try to do something =)\n";
            appr += getRandomVec(appr.size(), -5.0, 5.0);
            continue;
        }
        std::valarray<double> v = fun(appr);
        if ( sqrt((v*v).sum()) < 1E-6) {
//            clog << "Early out\n";
            break;
        }
    }
//    cout << iterCount << " iteration(s)" << endl;

    return appr;
}

std::valarray<double> getRandomVec(size_t sz, double low, double upper)
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    time_t now_c = std::chrono::system_clock::to_time_t(now);

    std::uniform_real_distribution<double> unif(low, upper);
    std::default_random_engine re(now_c);
    std::valarray<double> v(sz);
    for (auto& elem : v)
        elem = unif(re);
    return v;
}


#endif // NESYSTEM_H
