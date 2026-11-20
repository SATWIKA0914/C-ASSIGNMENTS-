#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

struct Resource {
    string name;
    explicit Resource(string n) : name(std::move(n)) {
        cout << "created " << name << '\n';
    }
    ~Resource() noexcept { cout << "destroyed " << name << '\n'; }
};

double parseAmount(const string& text) {
    size_t used = 0;
    double value = stod(text, &used);
    if (used != text.size()) throw invalid_argument("invalid numeric text");
    if (value < 0) throw invalid_argument("negative amount");
    return value;
}

void runTests() {
    auto resource = make_unique<Resource>("billing-session");
    try {
        cout << "valid: " << parseAmount("1500") << '\n';
        cout << "bad text: " << parseAmount("abc") << '\n';
    } catch (const invalid_argument& e) {
        cout << "caught: " << e.what() << '\n';
    }

    try {
        if (60000 > 50000) throw runtime_error("claim above cover");
    } catch (const exception& e) {
        cout << "caught: " << e.what() << '\n';
    }

    try {
        throw runtime_error("unknown package code");
    } catch (const exception& e) {
        cout << "caught: " << e.what() << '\n';
    }

    try {
        vector<int> huge;
        huge.reserve(huge.max_size());
        huge.reserve(huge.max_size());
        cout << "allocation succeeded\n";
    } catch (const bad_alloc&) {
        cout << "caught: bad_alloc\n";
    } catch (const length_error&) {
        cout << "caught: length_error (request too large)\n";
    } catch (...) {
        cout << "caught: unknown allocation error\n";
    }
}

int main() {
    try {
        runTests();
    } catch (...) {
        cout << "top-level handler caught an unexpected error\n";
    }
    cout << "program continues\n";
}
