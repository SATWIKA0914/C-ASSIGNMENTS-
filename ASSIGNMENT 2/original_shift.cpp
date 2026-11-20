#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

class ShiftHistory {
    static const int CAP = 10;
    int a[CAP]{};
    int count = 0;
public:
    void add(int value) {
        if (count < CAP) a[count++] = value;
        else {
            for (int i = 1; i < CAP; ++i) a[i - 1] = a[i];
            a[CAP - 1] = value;
        }
    }
};
int main() {
    const int N = 1000000;
    ShiftHistory h;
    auto start = steady_clock::now();
    for (int i = 0; i < N; ++i) h.add(i);
    auto end = steady_clock::now();
    cout << "Shift design, additions: " << N << '\n';
    cout << "Elapsed microseconds: "
         << duration<double, micro>(end - start).count() << '\n';
}
