#include <iostream>
#include <cmath>

#define n 100 // Number of intervals

double f(double x) {
    // Example function
    // Uncomment one of the return statements to use different functions
    
    // Function 1
    // return pow(x, 2);
    
    // Function 2
    return (cos(pow(x, 2) + 0.5) / (1.1 + sin(0.7 * x + 0.4)));
    
    // Function 3
    // return (x - 1) / (pow(x, 2) + x);
}

double trapezoid(double a, double b) {
    double value = (f(a) + f(b)) / 2;
    double h = (b - a) / n;
    double x[n];
    for (int i = 1; i < n; i++) {
        x[i] = (a + ((double)i / (double)n) * (b - a));
    }
    for (int i = 1; i < n; i++) {
        value += f(x[i]);
    }
    return value * h;
}

int main() {
    // Example usage
    double a = 0; // Lower limit
    double b = 1; // Upper limit
    double result = trapezoid(a, b);
    std::cout << "Result: " << result << std::endl;
    return 0;
}
