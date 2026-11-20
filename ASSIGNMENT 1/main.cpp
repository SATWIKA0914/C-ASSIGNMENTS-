#include <iostream>
#include <string>
using namespace std;

enum class Zone { Inner, Middle, Outer, Airport };
enum class DayType { Weekday, Weekend };

class MonthlyPass {
private:
    bool active;
    bool zoneAllowed[4];
public:
    MonthlyPass(int firstZone, int secondZone) : active(true), zoneAllowed{false, false, false, false} {
        if (firstZone >= 0 && firstZone < 4) zoneAllowed[firstZone] = true;
        if (secondZone >= 0 && secondZone < 4) zoneAllowed[secondZone] = true;
    }
    bool covers(Zone zone) const {
        return active && zoneAllowed[static_cast<int>(zone)];
    }
};

class SmartCard {
private:
    long long balancePaise;
    static constexpr long long MIN_BALANCE_PAISE = 5000;
public:
    explicit SmartCard(long long initial) : balancePaise(initial) {}
    long long balance() const { return balancePaise; }
    bool deduct(long long amount) {
        if (amount < 0 || balancePaise - amount < MIN_BALANCE_PAISE) return false;
        balancePaise -= amount;
        return true;
    }
};

long long baseFare(Zone zone) {
    constexpr long long FARES[] = {1000, 2000, 3000, 6000};
    return FARES[static_cast<int>(zone)];
}

long long calculateFare(Zone zone, DayType day, bool peak) {
    long long fare = baseFare(zone);
    // Weekend discount replaces peak surcharge; the two never combine.
    if (day == DayType::Weekend) {
        fare = fare * 90 / 100;
    } else if (peak) {
        fare = fare * 120 / 100;
    }
    return fare;
}

int main() {
    SmartCard card(20000);
    MonthlyPass pass(0, 1); // pass covers Inner and Middle zones

    struct Test { Zone zone; DayType day; bool peak; };
    Test tests[] = {
        {Zone::Inner, DayType::Weekday, false},
        {Zone::Outer, DayType::Weekday, true},
        {Zone::Airport, DayType::Weekend, true},
        {Zone::Middle, DayType::Weekend, false}
    };

    for (const Test& t : tests) {
        if (pass.covers(t.zone)) {
            cout << "Monthly pass: journey free in covered zone\n";
            continue;
        }
        long long f = calculateFare(t.zone, t.day, t.peak);
        cout << "Fare: " << f << " paise; ";
        if (card.deduct(f)) cout << "approved";
        else cout << "denied (minimum balance rule)";
        cout << "; balance: " << card.balance() << " paise\n";
    }
    return 0;
}
