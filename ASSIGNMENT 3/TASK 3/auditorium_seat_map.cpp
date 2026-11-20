#include <iostream>
using namespace std;

class Event {
    int rows, seats;
    bool** booked;

public:
    Event(int r, int s) : rows(r > 0 ? r : 0), seats(s > 0 ? s : 0),
                          booked(new bool*[rows]) {
        for (int i = 0; i < rows; ++i) {
            booked[i] = new bool[seats]{};
        }
        cout << "Event created: " << rows << " x " << seats << '\n';
    }

    bool book(int r, int s) {
        if (r < 0 || r >= rows || s < 0 || s >= seats || booked[r][s])
            return false;
        booked[r][s] = true;
        return true;
    }

    bool cancel(int r, int s) {
        if (r < 0 || r >= rows || s < 0 || s >= seats || !booked[r][s])
            return false;
        booked[r][s] = false;
        return true;
    }

    ~Event() {
        int count = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < seats; ++j)
                if (booked[i][j]) ++count;
            delete[] booked[i];
        }
        delete[] booked;
        cout << "Event closed. Booked seats: " << count << '\n';
    }
};

int main() {
    Event stackEvent(2, 3);
    stackEvent.book(0, 1);
    stackEvent.book(1, 2);
    stackEvent.cancel(0, 1);

    Event* heapEvent = new Event(3, 4);
    heapEvent->book(2, 2);
    delete heapEvent;

    {
        Event blockEvent(1, 2);
        blockEvent.book(0, 0);
    }

    Event zeroEvent(0, 5);
}
