#include <iostream>
#include <string>
using namespace std;

// INTENTIONALLY UNSAFE: compiler-generated copying duplicates the raw pointer.
// Both objects attempt to delete the same array. Use only to observe ASan failure.
class Prescription {
    int n;
    string* medicines;
public:
    explicit Prescription(int count)
        : n(count), medicines(new string[count]) {}
    ~Prescription() { delete[] medicines; }
    void set(int i, const string& m) { medicines[i] = m; }
    string get(int i) const { return medicines[i]; }
};

int main() {
    Prescription p(1);
    p.set(0, "Paracetamol");
    Prescription q = p; // Shallow copy: shared pointer.
    cout << q.get(0) << '\n';
}
