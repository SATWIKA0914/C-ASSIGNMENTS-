#include <iostream>
#include <string>
using namespace std;

class Address {
    string city;
    int pin;
public:
    Address(string c, int p) : city(c), pin(p) {}
    string str() const { return city + "-" + to_string(pin); }
};

class Student {
    string name;
    Address* home;

public:
    Student(string n, string city, int pin)
        : name(n), home(new Address(city, pin)) {}

    Student(const Student& other)
        : name(other.name),
          home(new Address(*other.home)) {}

    Student& operator=(const Student& other) {
        if (this != &other) {
            name = other.name;
            *home = *other.home;
        }
        return *this;
    }

    ~Student() { delete home; }

    void print() const { cout << name << " " << home->str() << '\n'; }
};

int main() {
    Student a("Kavya", "Salem", 636001);
    Student b = a;
    a.print();
    b.print();
}
