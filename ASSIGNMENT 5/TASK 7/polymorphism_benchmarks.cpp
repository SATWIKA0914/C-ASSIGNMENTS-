#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>
#include <variant>
#include <vector>
using namespace std;
using Clock = chrono::steady_clock;

struct Bill {
    virtual double total() const = 0;
    virtual ~Bill() = default;
};
struct OP : Bill {
    double a, b;
    OP(double x, double y) : a(x), b(y) {}
    double total() const override { return a + b; }
};
struct IP : Bill {
    double days, rate, surgery;
    IP(double d, double r, double s) : days(d), rate(r), surgery(s) {}
    double total() const override { return days * rate + surgery; }
};

struct PlainBill {
    int type;
    double a, b, c;
};
double switchTotal(const PlainBill& x) {
    switch (x.type) {
    case 0: return x.a + x.b;
    case 1: return x.a * x.b + x.c;
    default: return 0;
    }
}

struct VOP {
    double a, b;
    double total() const { return a + b; }
};
struct VIP {
    double days, rate, surgery;
    double total() const { return days * rate + surgery; }
};
using VariantBill = variant<VOP, VIP>;
double visitTotal(const VariantBill& v) {
    return visit([](const auto& x) { return x.total(); }, v);
}

template<class F>
double measure(F f) {
    auto start = Clock::now();
    double result = f();
    auto end = Clock::now();
    volatile double sink = result;
    (void)sink;
    return chrono::duration<double, milli>(end - start).count();
}

int main() {
    cout << fixed << setprecision(3);
    for (size_t n : {size_t(10), size_t(1000), size_t(1000000), size_t(10000000)}) {
        vector<unique_ptr<Bill>> virtualBills;
        vector<PlainBill> switchBills;
        vector<VariantBill> variantBills;
        virtualBills.reserve(n);
        switchBills.reserve(n);
        variantBills.reserve(n);

        for (size_t i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                virtualBills.push_back(make_unique<OP>(500, 1200));
                switchBills.push_back({0, 500, 1200, 0});
                variantBills.push_back(VOP{500, 1200});
            } else {
                virtualBills.push_back(make_unique<IP>(3, 2500, 40000));
                switchBills.push_back({1, 3, 2500, 40000});
                variantBills.push_back(VIP{3, 2500, 40000});
            }
        }

        double expected = 0;
        for (const auto& b : switchBills) expected += switchTotal(b);

        double tv = measure([&] {
            double s = 0;
            for (const auto& b : virtualBills) s += b->total();
            return s;
        });
        double ts = measure([&] {
            double s = 0;
            for (const auto& b : switchBills) s += switchTotal(b);
            return s;
        });
        double tvar = measure([&] {
            double s = 0;
            for (const auto& b : variantBills) s += visitTotal(b);
            return s;
        });

        double actual = 0;
        for (const auto& b : virtualBills) actual += b->total();
        cout << "Bills: " << n
             << " | agree: " << boolalpha << (actual == expected)
             << " | virtual ms: " << tv
             << " | switch ms: " << ts
             << " | variant ms: " << tvar << '\n';
    }
}
