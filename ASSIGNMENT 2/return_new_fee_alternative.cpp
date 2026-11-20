#include <iostream>
long long applyConcession(long long fee, int percent) {
    return fee - fee * percent / 100;
}
int main() {
    long long hostelFee = 45000;
    hostelFee = applyConcession(hostelFee, 10);
    std::cout << "Fee after returned concession: " << hostelFee << '\n';
}
