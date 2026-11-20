#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Prescription {
    vector<string> medicines;
public:
    explicit Prescription(int n) : medicines(n < 0 ? 0 : n) {}
    void set(int i, const string& value) {
        if (i >= 0 && i < static_cast<int>(medicines.size()))
            medicines[i] = value;
    }
    string get(int i) const {
        if (i < 0 || i >= static_cast<int>(medicines.size())) return "";
        return medicines[i];
    }
};

int main() {
    Prescription p(2);
    p.set(0, "Paracetamol");
    p.set(1, "ORS");
    Prescription q = p;
    q.set(1, "Cetirizine");
    cout << p.get(1) << " | " << q.get(1) << '\n';
}
