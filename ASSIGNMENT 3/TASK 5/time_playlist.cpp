#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

class Time {
    int seconds;
public:
    explicit Time(int s = 0) : seconds(s < 0 ? 0 : s) {}
    Time& operator++() {
        ++seconds;
        return *this;
    }
    Time operator++(int) {
        Time old = *this;
        ++seconds;
        return old;
    }
    bool operator==(const Time& t) const { return seconds == t.seconds; }
    bool operator<(const Time& t) const { return seconds < t.seconds; }
    void print() const {
        cout << seconds / 3600 << ':'
             << (seconds / 60) % 60 << ':'
             << seconds % 60;
    }
};

class Playlist {
    vector<string> tracks;
public:
    Playlist(initializer_list<string> t) : tracks(t) {}
    string& operator[](int i) {
        if (i < 0 || i >= static_cast<int>(tracks.size()))
            throw out_of_range("Playlist index out of range");
        return tracks[i];
    }
    const string& operator[](int i) const {
        if (i < 0 || i >= static_cast<int>(tracks.size()))
            throw out_of_range("Playlist index out of range");
        return tracks[i];
    }
    int size() const { return static_cast<int>(tracks.size()); }
};

int main() {
    Time t(5);
    Time a = t++;
    Time b = ++t;
    cout << a.operator==(Time(5)) << ' ';
    a.print(); cout << ' ';
    b.print(); cout << ' ';
    t.print(); cout << '\n';

    Playlist p{"Song A", "Song B", "Song C"};
    cout << p[1] << '\n';
    try {
        cout << p[3] << '\n';
    } catch (const out_of_range& e) {
        cout << e.what() << '\n';
    }

    Time nearHour(3599);
    ++nearHour;
    nearHour.print();
    cout << '\n';
}
