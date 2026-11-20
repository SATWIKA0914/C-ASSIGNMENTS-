#include <iostream>
#include <string>
using namespace std;

class Cart {
    string customer;
    double amount;

public:
    Cart(string c, double a) : customer(c), amount(a) {}
    double total() const { return amount; }
    string getCustomer() const { return customer; }
};

int main() {
    Cart a("Asha", 350), b("Bala", 520), c("Charan", 410);
    Cart* carts[] = {&a, &b, &c};

    int best = 0;
    for (int i = 1; i < 3; ++i) {
        if (carts[i]->total() > carts[best]->total())
            best = i;
    }

    cout << "Highest cart: " << carts[best]->getCustomer()
         << " " << carts[best]->total() << '\n';
}
