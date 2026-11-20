#include <iostream>
#include <string>
using namespace std;

class Staff {
    string name;
    int type; // 1 Professor, 2 LabAssistant, 3 GuestFaculty
    double basic, research, hours, rate;

public:
    Staff(string n, int t, double b, double r, double h, double rt)
        : name(n), type(t), basic(b), research(r), hours(h), rate(rt) {}

    double pay() const {
        switch (type) {
        case 1: return basic * 1.42 + research;
        case 2: return basic * 1.42;
        case 3: return hours * rate;
        default: return 0;
        }
    }
    void print() const { cout << name << ": " << pay() << '\n'; }
};

int main() {
    Staff a("Anu", 1, 50000, 5000, 0, 0);
    Staff b("Ravi", 2, 30000, 0, 0, 0);
    Staff c("Maya", 3, 0, 0, 20, 800);
    a.print();
    b.print();
    c.print();
}
