#include <iostream>
#include <vector>
using namespace std;

class Event {
    vector<vector<bool>> booked;
public:
    Event(int rows, int seats)
        : booked(rows > 0 ? rows : 0,
                 vector<bool>(seats > 0 ? seats : 0, false)) {}
    bool book(int r, int s) {
        if (r < 0 || r >= static_cast<int>(booked.size()) ||
            s < 0 || s >= static_cast<int>(booked[r].size()) || booked[r][s])
            return false;
        booked[r][s] = true;
        return true;
    }
    void print() const {
        for (const auto& row : booked) {
            for (bool seat : row) cout << (seat ? 'X' : 'O') << ' ';
            cout << '\n';
        }
    }
};

int main() {
    Event e(2, 3);
    e.book(0, 1);
    e.print();
}
