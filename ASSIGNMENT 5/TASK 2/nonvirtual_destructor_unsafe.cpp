#include <iostream>
using namespace std;

struct Bill {
    ~Bill() { cout << "~Bill\n"; }
    virtual double total() const = 0;
};
struct OPBill : Bill {
    int* data;
    OPBill() : data(new int[100]) {}
    ~OPBill() { delete[] data; cout << "~OPBill\n"; }
    double total() const override { return 500; }
};

int main() {
    Bill* b = new OPBill;
    cout << b->total() << '\n';
    delete b; // Undefined behaviour: deleting derived object via non-virtual base destructor.
}
