#include <iostream>
#include <cmath>

#define epsilon 0.01

using namespace std;

// Calculating the midpoint
double x_mid(double a, double b) {
    return (a + b) * 0.5;
}

// Example function
double f(double x) {
    return 3 * pow(x, 2) + 20 * x + 9;
}

// Checking the necessary condition
bool necessary_condition(double a, double b) {
    return (f(a) * f(b) < 0);
}

// First derivative
double f_prime1(double x) {
    return 6 * x + 20;
}

// Second derivative
double f_prime2(double x) {
    return 6; // Placeholder
}

// Checking the convergence condition
bool convergence_condition(double a, double b) {
    return ((f_prime1(a) * f_prime2(b) >= 0) && (f_prime2(a) * f_prime2(b) >= 0));
}

double bisection_method(double a, double b) {
    cout << "BISECTION METHOD" << endl;
    int i = 0;
    double x = 0;
    if (necessary_condition(a, b)) {
        while (abs(f(x)) >= epsilon) {
            x = x_mid(a, b);
            if (f(a) * f(x) < 0) {
                b = x;
            } else {
                a = x;
            }
            i++;
            cout << "Iteration: " << i << " x_mid: " << x << " f(x_mid) : " << f(x) << endl;
        }
    } else {
        cout << "Necessary condition not met" << endl;
    }
    return x;
}

double newton_method(double a, double b) {
    cout << "NEWTON'S METHOD" << endl;
    int i = 0;
    double xn = 0, x = 0;
    if (necessary_condition(a, b) && convergence_condition(a, b)) {
        x = (f(a) == f_prime2(a)) ? a : b;
        while (!(abs(f(x)) < epsilon || (abs(f(x) - xn) < epsilon))) {
            xn = x;
            x = x - (f(x) / f_prime1(x));
            i++;
            cout << "Iteration: " << i << " x: " << x << " f(x_mid) : " << f(x) << endl;
        }
    } else {
        cout << "Necessary or convergence condition not met" << endl;
    }
    return x;
}

double secant_method(double a, double b) {
    cout << "SECANT METHOD" << endl;
    int i = 0;
    double xn = 0, x = 0;
    if (necessary_condition(a, b) && convergence_condition(a, b)) {
        bool formula = true;
        if (f(a) == f_prime2(a)) {
            x = b;
            formula = false;
        } else {
            x = a;
        }
        while (!(abs(f(x)) < epsilon || (abs(f(x) - xn) < epsilon))) {
            xn = x;
            if (formula) {
                x = x - (f(x) / (f(b) - f(x))) * (b - x);
            } else {
                x = x - (f(x) / (f(x) - f(a))) * (x - a);
            }
            i++;
            cout << "Iteration: " << i << " x: " << x << " f(x_mid) : " << f(x) << endl;
        }
    } else {
        cout << "Necessary or convergence condition not met" << endl;
    }
    return x;
}

int main() {
    double a = -3, b = 5;
    cout << endl << "Solution for epsilon = " << epsilon << " using bisection method is x_mid = " << bisection_method(a, b) << endl << endl;
    cout << endl << "Solution for epsilon = " << epsilon << " using Newton's method is x_mid = " << newton_method(a, b) << endl << endl;
    cout << endl << "Solution for epsilon = " << epsilon << " using secant method is x_mid = " << secant_method(a, b) << endl << endl;
    return 0;
}
