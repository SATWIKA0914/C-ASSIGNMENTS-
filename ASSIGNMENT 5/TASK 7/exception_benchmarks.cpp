#include <chrono>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;
using Clock = chrono::steady_clock;

bool validateReturn(double amount) {
    return amount >= 0;
}
void validateThrow(double amount) {
    if (amount < 0) throw invalid_argument("negative");
}

template<class F>
double timeIt(F f) {
    auto a = Clock::now();
    volatile long long result = f();
    (void)result;
    auto b = Clock::now();
    return chrono::duration<double, milli>(b - a).count();
}

int main() {
    const int n = 1000000;
    cout << fixed << setprecision(3);
    for (int percent : {0, 1, 50}) {
        vector<double> values(n, 100.0);
        int invalid = n * percent / 100;
        for (int i = 0; i < invalid; ++i) values[i] = -1;

        double returnMs = timeIt([&] {
            long long accepted = 0;
            for (double x : values) if (validateReturn(x)) ++accepted;
            return accepted;
        });

        double exceptionMs = timeIt([&] {
            long long accepted = 0;
            for (double x : values) {
                try {
                    validateThrow(x);
                    ++accepted;
                } catch (const invalid_argument&) {
                    // Rejected claim; continue with the next claim.
                }
            }
            return accepted;
        });

        cout << "Invalid " << percent << "% | return-code ms: " << returnMs
             << " | exception ms: " << exceptionMs << '\n';
    }
}
