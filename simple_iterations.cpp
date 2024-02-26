#include <iostream>
#include <cmath>
#include <vector>

class SimpleIteration {
private:
    int size;
    std::vector<std::vector<double>> a;
    std::vector<double> b;
    std::vector<double> x;
    std::vector<double> xOld;

public:
    SimpleIteration(int size) {
        this->size = size;
        fill();
        print();
        transform();
        printResults();
    }

    // Initialize matrix A and vector b
    void fill() {
        a = {{3, 1, 2}, {1, -4, 1}, {1, 2, 3}};
        b = {5, -7, 2};
        x.resize(size, 0);
        xOld.resize(size, 0);
    }

    // Print matrix A and vector b
    void print() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                double rounded = round(a[i][j] * 1000) / 1000.0;
                std::cout << rounded << ", ";
            }
            std::cout << round(b[i] * 10000) / 10000.0 << std::endl;
        }
    }

    // Print the results (solution vector x)
    void printResults() {
        std::cout << std::endl;
        for (int i = 0; i < size; ++i) {
            std::cout << round(x[i] * 10000) / 10000.0 << " | ";
        }
    }

    // Perform the transformation iteratively
    void transform() {
        int iterations = 10; // Number of iterations
        for (int k = 0; k < iterations; ++k) {
            for (int i = 0; i < size; ++i) {
                xOld[i] = x[i];
                x[i] = g(i);
                for (int j = 0; j < size; ++j) {
                    x[i] += h(i, j) * xOld[j];
                }
            }
        }
    }

    // Calculate the next value for x[i]
    double g(int i) {
        return b[i] / a[i][i];
    }

    // Calculate the coefficient for xOld[j] in the update equation for x[i]
    double h(int i, int j) {
        if (i == j) {
            return 0;
        } else {
            return -a[i][j] / a[i][i];
        }
    }
};

int main() {
    SimpleIteration obj(3); // Create an object with matrix size 3
    return 0;
}
