#include <iomanip>
#include <iostream>
using namespace std;

class Money {
    long long paise;

public:
    Money(long long rupees = 0, int p = 0) : paise(rupees * 100 + p) {}

    Money operator+(const Money& other) const {
        Money result;
        result.paise = paise + other.paise;
        return result;
    }
    Money operator-(const Money& other) const {
        Money result;
        result.paise = paise - other.paise;
        return result;
    }
    Money& operator+=(const Money& other) {
        paise += other.paise;
        return *this;
    }
    bool operator==(const Money& other) const {
        return paise == other.paise;
    }
    bool operator<(const Money& other) const {
        return paise < other.paise;
    }
    friend ostream& operator<<(ostream& out, const Money& m) {
        long long value = m.paise;
        if (value < 0) {
            out << "-Rs " << (-value) / 100 << '.'
                << setw(2) << setfill('0') << (-value) % 100;
        } else {
            out << "Rs " << value / 100 << '.'
                << setw(2) << setfill('0') << value % 100;
        }
        out << setfill(' ');
        return out;
    }
};

int main() {
    Money a(120, 75), b(79, 25);
    Money c = a + b;
    cout << c << '\n' << boolalpha << (c == Money(200)) << '\n';

    Money x(0, 75), y(0, 50);
    cout << x + y << '\n';
    cout << Money(1) - Money(2) << '\n';
    c += Money(5);
    cout << c << '\n';
}
