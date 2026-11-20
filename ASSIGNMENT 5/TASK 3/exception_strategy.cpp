#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class BillingError : public runtime_error {
public:
    using runtime_error::runtime_error;
};
class ClaimError : public BillingError {
public:
    using BillingError::BillingError;
};
class PackageError : public BillingError {
public:
    using BillingError::BillingError;
};

double calculate(double charge) {
    if (charge < 0) throw invalid_argument("negative charge");
    return charge;
}

double claim(double bill, double cover) {
    if (bill > cover) throw ClaimError("claim exceeds cover");
    return bill;
}

double packageRate(const string& code) {
    if (code == "DC100") return 25000;
    if (code == "DC200") return 40000;
    throw PackageError("unknown package");
}

void logAndRethrow() {
    try {
        (void)claim(60000, 50000);
    } catch (const ClaimError& e) {
        cout << "audit: " << e.what() << '\n';
        throw;
    }
}

int main() {
    try {
        cout << calculate(100) << '\n';
        cout << packageRate("DC100") << '\n';
        logAndRethrow();
    } catch (const exception& e) {
        cout << "reported: " << e.what() << '\n';
    }
}
