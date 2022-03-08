#include "NewtonIteration.h"
#include <cmath>
#include <iostream>

double sqrt_newton(double num, double x0, double err, int maxiter, bool print) {
    // The square root of a is the root of the following function:
    // f(x) = x^2 - a
    // Then, we have that:
    // f'(x) = 2x
    // So the Newton's method becomes:
    // x_{n+1} = x_n - f(x_n) / f'(x_n)
    //         = x_n - (x_n^2 - a) / (2x_n)
    //         = x_n - x_n/2 + a / (2x_n)
    //         = 1/2 * (x_n + a / x_n)

    // A lambda function for the newton step
    auto newton_step = [&](double xn) {double inv_xn = 1.0 / xn;
                                     double xnp = 0.5 * (xn + num * inv_xn);
                                       return xnp;};
    double xn, xnp, current_err;
    xn = x0;

    if(print) std::cout << "The steps: " << xn;

    for(int i = 1; i <= maxiter; i++) {
        xnp = newton_step(xn);
        if(print) std:: cout << " -> " << xnp;
        current_err = std::abs(xnp - xn);
        if(current_err < err) {
            if(print) std::cout << "\nConverged after " << i << " iterations!";
            break;
        }
        xn = xnp;
    }
    if(print) std::cout << "\nAchieved error: " << current_err << std::endl;
    return xnp;

}

double sqrt_newton(double num, double x0) {
    double err = 1e-7;
    int maxiter = 100;
    bool print = true;
    return sqrt_newton(num, x0, err, maxiter, print);
}