#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

class CircularHistory {
    static const int CAP = 10;
    int a[CAP]{};
    int start = 0;
    int count = 0;
public:
    void add(int value) {
        if (count < CAP) {
            a[(start + count) % CAP] = value;
            ++count;
        } else {
            a[start] = value;
            start = (start + 1) % CAP;
        }
    }
};
int main() {
    const int N = 1000000;
    CircularHistory h;
    auto start = steady_clock::now();
    for (int i = 0; i < N; ++i) h.add(i);
    auto end = steady_clock::now();
    cout << "Circular design, additions: " << N << '\n';
    cout << "Elapsed microseconds: "
         << duration<double, micro>(end - start).count() << '\n';
}
