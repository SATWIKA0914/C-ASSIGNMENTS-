#include <iostream>
#include <string>
using namespace std;

class Book {
    string title;
    int copies;

public:
    Book() : Book("Untitled", 0) {}
    explicit Book(string t) : Book(t, 1) {}
    Book(string t, int c) : title(t), copies(c < 0 ? 0 : c) {}

    void print() const {
        cout << title << " | copies: " << copies << '\n';
    }
};

int main() {
    Book empty;
    Book donated("C++ Basics");
    Book full("Data Structures", 5);
    Book invalid("Invalid Book", -4);

    empty.print();
    donated.print();
    full.print();
    invalid.print();

    // Book converted = "C Programming"; // Does not compile because constructor is explicit.
    Book converted("C Programming");
    converted.print();
}
