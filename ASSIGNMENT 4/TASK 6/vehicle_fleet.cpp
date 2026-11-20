#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Vehicle {
protected:
    string regNo;
    double dailyRate;
    bool rented = false;

public:
    Vehicle(string r, double rate) : regNo(r), dailyRate(rate) {}
    virtual double charge(int days) const = 0;
    virtual string type() const = 0;

    void rent() {
        if (!rented) {
            rented = true;
            cout << regNo << " rented\n";
        } else {
            cout << regNo << " is already rented\n";
        }
    }

    void giveBack(int daysLate = 0) {
        if (rented) {
            cout << regNo << " returned. Amount: "
                 << charge(1) + daysLate * dailyRate * 1.5 << '\n';
            rented = false;
        } else {
            cout << regNo << " was not rented\n";
        }
    }

    void list() const {
        cout << type() << " " << regNo << " rate/day " << dailyRate
             << (rented ? " [Rented]\n" : " [Available]\n");
    }

    virtual ~Vehicle() = default;
};

class Bicycle : public Vehicle {
public:
    Bicycle(string r, double rate) : Vehicle(r, rate) {}
    double charge(int days) const override { return dailyRate * days; }
    string type() const override { return "Bicycle"; }
};

class MotorVehicle : public Vehicle {
protected:
    double fuelLevel;
    string serviceDue;

public:
    MotorVehicle(string r, double rate, double fuel, string due)
        : Vehicle(r, rate), fuelLevel(fuel), serviceDue(due) {}
};

class TwoWheeler : public MotorVehicle {
public:
    TwoWheeler(string r, double rate, double fuel, string due)
        : MotorVehicle(r, rate, fuel, due) {}
    double charge(int days) const override { return dailyRate * days + 50; }
    string type() const override { return "TwoWheeler"; }
};

class Car : public MotorVehicle {
protected:
    int seats;

public:
    Car(string r, double rate, double fuel, string due, int s)
        : MotorVehicle(r, rate, fuel, due), seats(s) {}
    double charge(int days) const override { return dailyRate * days + 200; }
    string type() const override { return "Car"; }
};

class ElectricCar : public Car {
    double batteryKWh;

public:
    ElectricCar(string r, double rate, double chargeLevel,
                string due, int s, double battery)
        : Car(r, rate, chargeLevel, due, s), batteryKWh(battery) {}
    double charge(int days) const override {
        return dailyRate * days + batteryKWh * 2.0;
    }
    string type() const override { return "ElectricCar"; }
};

class ElectricBus : public MotorVehicle {
    int seats;
    double batteryKWh;

public:
    ElectricBus(string r, double rate, double chargeLevel,
                string due, int s, double battery)
        : MotorVehicle(r, rate, chargeLevel, due),
          seats(s), batteryKWh(battery) {}
    double charge(int days) const override {
        return dailyRate * days + batteryKWh * 2.0 + seats * 5.0;
    }
    string type() const override { return "ElectricBus"; }
};

int main() {
    vector<unique_ptr<Vehicle>> fleet;
    fleet.push_back(make_unique<Bicycle>("BI-101", 100));
    fleet.push_back(make_unique<TwoWheeler>("TW-202", 250, 5, "2026-12-01"));
    fleet.push_back(make_unique<Car>("CA-303", 1000, 20, "2026-12-10", 5));
    fleet.push_back(make_unique<ElectricCar>("EV-404", 1200, 80,
                                             "2026-12-15", 5, 60));
    fleet.push_back(make_unique<ElectricBus>("EB-505", 2500, 90,
                                             "2026-12-20", 30, 150));

    for (const auto& v : fleet)
        v->list();

    cout << "\nRenting vehicles:\n";
    for (const auto& v : fleet)
        v->rent();

    cout << "\nReturning first vehicle 2 days late:\n";
    fleet[0]->giveBack(2);

    cout << "\nRental charges for 2 days:\n";
    for (const auto& v : fleet)
        cout << v->type() << ": " << v->charge(2) << '\n';
}
