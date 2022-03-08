#include <iostream>
#include <iomanip>
#include <random>
#include "LinearFit.h"
#include "Linspace.h"

#define assertm(exp, msg) assert(((void)msg, exp))

int main(int, char **) {
    // The desired values:
    double m = 42.0, b = 137.0;
    // The lengths:
    int n = 101;
    // The x limits:
    double xmin = -100, xmax = 100;
    std::vector<double> xs(n), ys(n);

    xs = linspace(xmin, xmax, n);

    // adding a small noise (normal dist. with 0 mean, 0.01 std)
    std::random_device rd;
    std::mt19937 e2(rd());
    std::normal_distribution<> dist(0, 0.01);

    for (size_t i = 0; i < n; i++) {
        ys[i] = m * xs[i] + b + dist(e2);
    }

    auto res = linear_fit(xs, ys);

    std::cout << "The result of the fit is:\n";
    std::cout << "    m = " << res[0] << "\n";
    std::cout << "    b = " << res[1] << "\n";
    std::cout << "While the exact result is:\n";
    std::cout << "    m = " << m << "\n";
    std::cout << "    b = " << b << "\n";
    std::cout << "This means that the error is:\n";
    std::cout << "    dm = " << std::abs(res[0] - m) << "\n";
    std::cout << "    db = " << std::abs(res[1] - b);

}
