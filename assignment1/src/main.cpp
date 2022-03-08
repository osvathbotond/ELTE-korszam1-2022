#include <iostream>
#include <iomanip>
#include "NewtonIteration.h"

int main(int, char**) {
    // We want to see more digits:
    std::cout << std::setprecision(9);
    
    int num = 612;
    double x0 = 10;
    double sq = sqrt_newton(num, x0);
    std::cout << "The square root of " << num << " is " << sq;
}
