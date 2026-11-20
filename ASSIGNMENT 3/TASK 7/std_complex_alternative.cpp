#include <complex>
#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
    complex<double> resistor(100, 0), inductor(0, 31.4159);
    complex<double> series = resistor + inductor;
    cout << "Series: " << series << '\n';

    complex<double> denominator = resistor + inductor;
    if (abs(denominator) == 0) {
        cout << "Division by zero impedance\n";
    } else {
        cout << "Parallel: " << (resistor * inductor) / denominator << '\n';
    }
}
