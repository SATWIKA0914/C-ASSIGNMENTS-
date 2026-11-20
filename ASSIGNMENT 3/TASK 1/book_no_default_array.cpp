#include <string>
class Book {
    std::string title;
public:
    explicit Book(std::string t) : title(t) {}
};
int main() {
    Book books[3] = {Book("A"), Book("B"), Book("C")};
    (void)books;
    // Book books2[3]; // Uncomment: compilation fails; no default constructor exists.
}
