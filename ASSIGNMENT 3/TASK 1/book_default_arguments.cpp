#include <iostream>
#include <string>
using namespace std;

class Book {
    string title;
    int copies;

public:
    Book(string t = "Untitled", int c = 0)
        : title(t), copies(c < 0 ? 0 : c) {}

    void print() const { cout << title << " | " << copies << '\n'; }
};

int main() {
    Book a, b("C++"), c("Algorithms", 4), d("Bad", -2);
    a.print();
    b.print();
    c.print();
    d.print();
}
