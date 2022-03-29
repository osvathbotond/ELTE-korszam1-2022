#include <iostream>
#include "matrix.h"

int main(int, char **) {
    auto A = Matrix<int>({1, 2, 3, 4, 5, 6, 7, 8, 9});
    std::cout << A;
    auto B = Matrix<int>({2, 1, 1, 1, 1, 1, 1, 1, 1});
    auto C = Matrix<float>({5.f, 1.f, 8.f, 1.f, 1.f, 1.f, 1.f, 1.f, 7.f});
    auto D = A + B + C;
    std::cout << std::endl;
    std::cout << D;
    auto E = A - B;
    std::cout << std::endl;
    std::cout << E;
    auto F = A * C;
    std::cout << std::endl;
    std::cout << F;
    auto G = 2 * A;
    std::cout << std::endl;
    std::cout << G;
    auto H = A.transpose();
    std::cout << std::endl;
    std::cout << H;
    std::cout << std::endl;
    std::cout << B.trace();
    auto Q =  A*4;
    std::cout << std::endl;
    std::cout << Q;
    auto N =  C / 1.5f;
    std::cout << std::endl;
    std::cout << N;


}