#include <matplot/matplot.h>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

auto sinc(double x) -> double
{
    return sin(x) / x;
}

auto fraunhofer(double x, double lambda, double D, double y) -> double
{
    double b = M_PI * D * x / (lambda * y);
    return pow(sinc(b), 2);
}

auto opg1() -> void
{
    double lambda = 532; // nm
    double D      = 2;   // um
    double y      = 1;   // m

    auto x = matplot::linspace(0, 2, 1000);
    auto y = matplot::transform(x, [](auto x) { return fraunhofer(x, lambda, D, y); });
    matplot::plot(x, y);
    matplot::show();
}

auto opg2() -> void
{
    double lambda = 532; // nm
    double x      = 1;   // m

    auto D = matplot::linspace(0.1, 10, 1000);
    auto y = matplot::transform(D, [](auto D) { return fraunhofer(x, lambda, D, y); });
    matplot::plot(D, y);
    matplot::show();
}

auto main() -> int
{
    // opg1();
    opg2();

    return 0;
}
