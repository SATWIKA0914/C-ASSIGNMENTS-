#include <iostream>
#include <iomanip>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

class BillingError : public runtime_error {
public:
    using runtime_error::runtime_error;
};
class InvalidCharge : public BillingError {
public:
    using BillingError::BillingError;
};
class ClaimError : public BillingError {
public:
    using BillingError::BillingError;
};
class UnknownPackage : public BillingError {
public:
    using BillingError::BillingError;
};
class MissingPatient : public BillingError {
public:
    using BillingError::BillingError;
};

class Bill {
protected:
    string patient;
    explicit Bill(const string& p) : patient(p) {
        if (patient.empty()) throw MissingPatient("missing patient record");
    }
    static void check(double value) {
        if (value < 0) throw InvalidCharge("negative charge");
    }

public:
    virtual double total() const = 0;
    virtual string type() const = 0;
    virtual void print() const {
        cout << type() << ' ' << patient << ": " << total() << '\n';
    }
    virtual ~Bill() noexcept = default;
};

class OutPatientBill : public Bill {
    double consultation, tests;
public:
    OutPatientBill(const string& p, double c, double t)
        : Bill(p), consultation(c), tests(t) { check(c); check(t); }
    double total() const override { return consultation + tests; }
    string type() const override { return "OP"; }
};

class InPatientBill : public Bill {
    int days;
    double perDay, procedures, medicines;
public:
    InPatientBill(const string& p, int d, double rate, double proc, double med)
        : Bill(p), days(d), perDay(rate), procedures(proc), medicines(med) {
        if (d < 0) throw InvalidCharge("negative number of days");
        check(rate); check(proc); check(med);
    }
    double total() const override { return days * perDay + procedures + medicines; }
    string type() const override { return "IP"; }
};

class DayCareBill : public Bill {
    string package;
    double packagePrice;
public:
    DayCareBill(const string& p, const string& code, double price)
        : Bill(p), package(code), packagePrice(price) {
        if (package != "DC100" && package != "DC200")
            throw UnknownPackage("unknown package: " + package);
        check(price);
    }
    double total() const override { return packagePrice; }
    string type() const override { return "DayCare"; }
};

class EmergencyBill : public Bill {
    double base, hourly;
    int hours;
public:
    EmergencyBill(const string& p, double b, int h, double rate)
        : Bill(p), base(b), hourly(rate), hours(h) {
        check(b); check(rate);
        if (h < 0) throw InvalidCharge("negative emergency hours");
    }
    double total() const override { return base + hours * hourly; }
    string type() const override { return "Emergency"; }
};

class Payer {
public:
    virtual double amountCovered(const Bill& bill) const = 0;
    virtual string name() const = 0;
    virtual ~Payer() noexcept = default;
};

class SelfPay : public Payer {
public:
    double amountCovered(const Bill& bill) const override { return bill.total(); }
    string name() const override { return "SelfPay"; }
};

class Insurance : public Payer {
    double limit, copayPercent;
public:
    Insurance(double l, double c) : limit(l), copayPercent(c) {
        if (l < 0 || c < 0 || c > 100)
            throw ClaimError("invalid insurance policy");
    }
    double amountCovered(const Bill& bill) const override {
        double covered = bill.total() * (100.0 - copayPercent) / 100.0;
        return covered < limit ? covered : limit;
    }
    string name() const override { return "Insurance"; }
};

class GovernmentScheme : public Payer {
    double dc100Rate, dc200Rate;
public:
    GovernmentScheme(double a, double b) : dc100Rate(a), dc200Rate(b) {
        if (a < 0 || b < 0) throw ClaimError("invalid scheme rate");
    }
    double amountCovered(const Bill& bill) const override {
        if (bill.type() == "DayCare") {
            // Demonstration scheme package rate.
            return dc100Rate;
        }
        return bill.total() * 0.75;
    }
    string name() const override { return "GovernmentScheme"; }
};

class CorporatePayer : public Payer {
    double percent;
public:
    explicit CorporatePayer(double p) : percent(p) {
        if (p < 0 || p > 100) throw ClaimError("invalid corporate cover");
    }
    double amountCovered(const Bill& bill) const override {
        return bill.total() * percent / 100.0;
    }
    string name() const override { return "Corporate"; }
};

int main() {
    cout << fixed << setprecision(2);
    vector<unique_ptr<Bill>> bills;
    bills.push_back(make_unique<OutPatientBill>("Ravi", 500, 1200));
    bills.push_back(make_unique<InPatientBill>("Meena", 3, 2500, 40000, 5000));
    bills.push_back(make_unique<DayCareBill>("Asha", "DC100", 25000));
    bills.push_back(make_unique<EmergencyBill>("John", 2000, 3, 1500));

    double dayTotal = 0;
    for (const auto& b : bills) {
        b->print();
        dayTotal += b->total();
    }
    cout << "Day total: " << dayTotal << '\n';

    SelfPay self;
    Insurance insurance(50000, 20);
    GovernmentScheme scheme(18000, 30000);
    CorporatePayer corporate(60);
    const Payer* payers[] = {&self, &insurance, &scheme, &corporate};

    cout << "\nPayer coverage for first bill:\n";
    for (const Payer* p : payers)
        cout << p->name() << ": " << p->amountCovered(*bills[0]) << '\n';
}
