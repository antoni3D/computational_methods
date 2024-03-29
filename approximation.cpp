#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

#define n 2
#define trapezoid_n 100

// Lagrange Polynomials, recursive formula
double LagrangePoly(double example, double x) {
    if (example == 0) {
        return 1;
    } else if (example == 1) {
        return x;
    } else {
        return (LagrangePoly(example - 1, x) * (1 / (example)) * (2 * example - 1) * x) - (LagrangePoly(example - 2, x) * (example - 1) / (example));
    }
}

// Basic function
double f(double x) {
    return sqrt(pow(x, 2) + (2 * x) + 4);
}

// Functions adapted for numerical integration
double f_outputs(double x, int power, double p, int method) {
    switch (method) {
        case 1: // Function for integral, built from function * p(x) * x^i (LEAST SQUARES APPROXIMATION)
            return sqrt(pow(x, 2) + (2 * x) + 4) * p * pow(x, power);
        case 2: // ORTHOGONAL APPROXIMATION
            return p * pow(LagrangePoly(power, x), 2);
        case 3: // ORTHOGONAL APPROXIMATION
            return sqrt(pow(x, 2) + (2 * x) + 4) * LagrangePoly(power, x);
        default:
            return 1;
    }
}

// Trapezoidal integration from built function
double trapezoid(double a, double b, double p, int power, int method) {
    double value = (f_outputs(a, power, p, method) + f_outputs(b, power, p, method)) / 2;
    double h = (b - a) / trapezoid_n;
    double x[trapezoid_n];
    for (int i = 1; i < trapezoid_n; i++) {
        x[i] = (a + ((double) i / (double) trapezoid_n) * (b - a));
    }
    for (int i = 1; i < trapezoid_n; i++) {
        value += f_outputs(x[i], power, p, method);
    }
    return value * h;
}

// Gaussian Elimination
void gaussianElimination(vector<vector<double>>& matrix, vector<double>& output, vector<double>& result) {
    for (int x = 0; x < matrix.size() - 1; x++) {
        for (int i = x + 1; i < matrix.size(); i++) {
            double temp = matrix[i][x] / matrix[x][x];
            output[i] -= output[x] * temp;
            for (int j = x; j < matrix.size(); j++) {
                matrix[i][j] -= (matrix[x][j] * temp);
            }
        }
    }
    for (int i = matrix.size() - 1; i > -1; i--) {
        for (int j = matrix.size() - 1; j > i; j--) {
            output[i] = output[i] - matrix[i][j] * result[j];
        }
        result[i] = output[i] / matrix[i][i];
    }
}

// Print the array of results
void print_gaussianElimination(vector<double>& result) {
    cout << endl << "Gaussian Elimination Result:" << endl;
    for (int i = 0; i < result.size(); i++) {
        cout << "x[" << i << "] = " << result[i] << endl;
    }
}

// Least Squares Approximation
double least_squares_approximation(double a, double b, double x, double p, vector<vector<double>>& matrix, vector<double>& output, vector<double>& result) {
    double value = 0;
    // Build the Matrix
    for (int i = 0; i <= n; i++) {
        output[i] = trapezoid(a, b, p, i, 1);
        for (int j = 0; j <= n; j++) {
            matrix[i][j] = pow(b, i + j + 1) / (i + j + 1) * p - pow(a, i + j + 1) / (i + j + 1) * p;
        }
    }
    cout << "Approximation Matrix:" << endl;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << output[i] << endl;
    }
    gaussianElimination(matrix, output, result);
    print_gaussianElimination(result);
    // Calculate the result
    for (int i = 0; i < n + 1; i++) {
        value += result[i] * pow(x, i);
    }
    return value;
}

// Orthogonal Approximation
double orthogonal_approximation(double a, double b, double x, double p) {
    double value = 0;
    for (int i = 0; i <= n; i++) {
        // The first term is 1/𝜆 and the next term is Ci
        value += ((1.f / trapezoid(a, b, p, i, 2)) * trapezoid(a, b, p, i, 3)) * LagrangePoly(i, x);
    }
    return value;
}

// Least Squares Approximation
double least_squares_approximation(double x) {
    double x_points[5] = {-1, -0.5, 0, 0.5, 1};
    double y_points[5];
    for (int i = 0; i < 5; i++) {
        y_points[i] = f(x_points[i]);
    }
    vector<vector<double>> matrix(n + 1, vector<double>(n + 1));
    vector<double> output(n + 1);
    vector<double> result(n + 1);
    double value = 0;
    for (int i = 0; i <= n; i++) {
        // Loop through results
        for (int j = 0; j < 5; j++) {
            value += pow(x_points[j], i) * y_points[j];
        }
        // Loop through matrix
        for (int k = 0; k <= n; k++) {
            for (int l = 0; l < 5; l++) {
                matrix[i][k] += pow(x_points[l], i + k);
            }
        }
        output[i] = value;
        value = 0;
    }
    cout << endl;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << output[i];
        cout << endl;
    }
    value = 0;
    gaussianElimination(matrix, output, result);
    print_gaussianElimination(result);
    for (int i = 0; i <= n; i++) {
        value += result[i] * pow(x, i);
    }
    return value;
}


int main() {
    double a = -1, b = 1; // integration range
    double x = -0.25; // point at which we calculate the approximation
    double p = 1;
    vector<vector<double>> matrix(n + 1, vector<double>(n + 1));
    vector<double> output(n + 1);
    vector<double> result(n + 1);
    cout << "Approximation for a: " << a << " ,b: " << b << " ,p: " << p << " ,x: " << x << " ,n: " << n << endl;
    cout << endl << "Least Squares Approximation at point " << x << " : " << least_squares_approximation(a, b, x, p, matrix, output, result) << endl;
    cout << endl << "Orthogonal Approximation at point " << x << " : " << orthogonal_approximation(a, b, x, p) << endl;
    cout << endl << "Least Squares Approximation " << x << " : " << least_squares_approximation(x) << endl;
    return 0;
}
