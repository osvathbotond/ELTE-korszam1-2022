#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include "matrix.h"

// Progressbar to the stdout.
// Source: https://stackoverflow.com/a/36315819
#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60
void printProgress(double percentage) {
    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}

Matrix<float> generateNormalMatrix(int N, float mean, float std) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> d(mean, std);

    auto M = Matrix<float>(N);

    for (size_t i = 0; i < N * N; i++) {
        M.data[i] = d(gen);
    }

    return M;
}
template<typename T>
double measureMultiplication(Matrix<T> A, Matrix<T> B) {
    auto start = std::chrono::high_resolution_clock::now();
    auto AB = A * B;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    return diff.count();
}

double measureMultiplication(int N, float mean, float std) {
    auto A = generateNormalMatrix(N, mean, std);
    auto B = generateNormalMatrix(N, mean, std);

    return measureMultiplication(A, B);
}

int main(int, char **) {
    std::ofstream result_file;
    result_file.open ("result.txt");
    result_file << "# Result of the matrix multiplication test. The first column is the linear size of the matrices, and"
                   "the second one is the smallest time from 5 runs. \n";

    // Set the initial time to infinity. This way the measured one will be smaller, for sure.
    double best_time = HUGE_VAL;
    double new_time;
    // Reproducing the figure in the class notes.
    double total = 350 - 100 + 1;
    for(size_t N = 100; N <= 350; N++) {
        printProgress((N - 100 + 1.0) / total);

        // doing 10 runs and picking the lowest one.
        for(size_t i = 0; i < 10; i++) {
            new_time = measureMultiplication(N, 0.f, 100.f);
            if (new_time < best_time) {
                best_time = new_time;
            }
        }
        // Writing out then resetting the best time.
        result_file << N << " " << best_time << "\n";
        best_time = HUGE_VAL;
    }
    result_file.close();

}