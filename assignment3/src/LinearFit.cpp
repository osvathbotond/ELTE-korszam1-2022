#include "LinearFit.h"
#include <cmath>
#include <iostream>
#include <numeric>

std::array<double, 2> linear_fit(std::vector<double> xs, std::vector<double> ys) {
    if (xs.size() != ys.size()) {
        throw std::invalid_argument("the 2 input vectors must have identical lengths!");
    }
    double xsum = std::accumulate(xs.begin(), xs.end(), 0.0);
    double xbar = xsum / xs.size();

    double ysum = std::accumulate(ys.begin(), ys.end(), 0.0);
    double ybar = ysum / ys.size();

    double num = 0.0;
    for (size_t i = 0; i < xs.size(); i++) {
        num += (xs[i] - xbar) * (ys[i] - ybar);
    }
    double den = std::accumulate(xs.begin(), xs.end(), 0.0,
                                 [xbar](double val, double x) { return val + (x - xbar) * (x - xbar); });

    double m = num / den;

    double b = ybar - m * xbar;

    return std::array<double, 2>{m, b};
}