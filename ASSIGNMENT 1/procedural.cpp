#include <iostream>
using namespace std;

bool canTravel(long long balance, long long fare) {
    return fare >= 0 && balance - fare >= 5000;
}

bool deduct(long long& balance, long long fare) {
    if (!canTravel(balance, fare)) return false;
    balance -= fare;
    return true;
}

int main() {
    long long balance = 10000;
    long long fare = 2000;
    if (deduct(balance, fare)) cout << "Approved\n";
    else cout << "Denied\n";
    cout << "Balance: " << balance << " paise\n";
}
