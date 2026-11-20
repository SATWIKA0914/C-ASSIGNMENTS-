#include <cmath>
#include <iostream>
#include <stdexcept>
using namespace std;

class Complex {
    double real, imag;

public:
    Complex() : real(0), imag(0) {}
    Complex(double r) : real(r), imag(0) {}
    Complex(double r, double i) : real(r), imag(i) {}

    Complex operator+(const Complex& z) const {
        return Complex(real + z.real, imag + z.imag);
    }
    Complex operator-(const Complex& z) const {
        return Complex(real - z.real, imag - z.imag);
    }
    Complex operator*(const Complex& z) const {
        return Complex(real * z.real - imag * z.imag,
                       real * z.imag + imag * z.real);
    }
    Complex operator/(const Complex& z) const {
        double denominator = z.real * z.real + z.imag * z.imag;
        if (denominator == 0)
            throw domain_error("Division by zero impedance");
        return Complex((real * z.real + imag * z.imag) / denominator,
                       (imag * z.real - real * z.imag) / denominator);
    }
    bool operator==(const Complex& z) const {
        return real == z.real && imag == z.imag;
    }
    double magnitude() const { return sqrt(real * real + imag * imag); }

    friend ostream& operator<<(ostream& out, const Complex& z) {
        out << z.real;
        if (z.imag >= 0) out << " + j" << z.imag;
        else out << " - j" << -z.imag;
        return out;
    }
};

int main() {
    const double pi = acos(-1.0);
    double frequency = 50.0, L = 0.1, C = 100e-6;
    double w = 2 * pi * frequency;

    Complex resistor(100, 0);
    Complex inductor(0, w * L);
    Complex capacitor(0, -1.0 / (w * C));

    Complex series = resistor + inductor + capacitor;
    cout << "Series impedance: " << series << '\n';
    cout << "Magnitude: " << series.magnitude() << '\n';

    try {
        Complex parallel = (resistor * inductor) / (resistor + inductor);
        cout << "Parallel R-L impedance: " << parallel << '\n';
        cout << "Magnitude: " << parallel.magnitude() << '\n';
        Complex invalid = resistor / Complex();
        cout << invalid << '\n';
    } catch (const domain_error& e) {
        cout << e.what() << '\n';
    }
}
