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

double simpson(double a, double b) {
    double valueX = 0, valueT = 0, value = 0;
    double x[n + 1];
    double t[n];
    
    // Calculate x values
    for (int i = 0; i <= n; i++) {
        x[i] = (a + ((double)i / (double)n) * (b - a));
        if ((i == 0) || (i == n)) {
            value += f(x[i]);
        } else {
            valueX += f(x[i]);
        }
    }
    
    double h = (x[n] - x[n - 1]) / 2;
    
    // Calculate t values
    for (int i = 0; i < n; i++) {
        t[i] = 0.5 * (x[i + 1] + x[i]);
        valueT += f(t[i]);
    }
    
    // Apply Simpson's rule formula
    value = (value + ((4 * valueT) + (2 * valueX))) * (h / 3.0);
    return value;
}

int main() {
    // Example usage
    double a = 0; // Lower limit
    double b = 1; // Upper limit
    double result = simpson(a, b);
    std::cout << "Result: " << result << std::endl;
    return 0;
}
