#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

class Bill {
public:
    virtual double total() const = 0;
    virtual string type() const = 0;
    virtual ~Bill() = default;
};

class OutPatientBill : public Bill {
    double consultation, tests;
public:
    OutPatientBill(double c, double t) : consultation(c), tests(t) {}
    double total() const override { return consultation + tests; }
    string type() const override { return "OutPatient"; }
};

class MaternityBill : public Bill {
    double package, medicines;
public:
    MaternityBill(double p, double m) : package(p), medicines(m) {}
    double total() const override {
        if (package < 0 || medicines < 0) throw invalid_argument("negative charge");
        return package + medicines;
    }
    string type() const override { return "Maternity"; }
};

class Payer {
public:
    virtual double amountCovered(const Bill& b) const = 0;
    virtual string name() const = 0;
    virtual ~Payer() = default;
};

class SelfPay : public Payer {
public:
    double amountCovered(const Bill& b) const override { return b.total(); }
    string name() const override { return "SelfPay"; }
};

class EmployeeBenefit : public Payer {
    double cap;
public:
    explicit EmployeeBenefit(double c) : cap(c) {}
    double amountCovered(const Bill& b) const override {
        double amount = b.total() * 0.9;
        return amount < cap ? amount : cap;
    }
    string name() const override { return "EmployeeBenefit"; }
};

int main() {
    vector<unique_ptr<Bill>> bills;
    bills.push_back(make_unique<OutPatientBill>(500, 1200));
    bills.push_back(make_unique<MaternityBill>(60000, 5000));

    SelfPay self;
    EmployeeBenefit employee(50000);
    const Payer* payers[] = {&self, &employee};

    for (const auto& bill : bills) {
        cout << bill->type() << " total " << bill->total() << '\n';
        for (const Payer* payer : payers)
            cout << payer->name() << " covers "
                 << payer->amountCovered(*bill) << '\n';
    }
}
