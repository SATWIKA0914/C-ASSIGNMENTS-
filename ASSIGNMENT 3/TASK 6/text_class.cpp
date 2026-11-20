#include <cstring>
#include <iostream>
using namespace std;

class Text {
    char* data;

public:
    Text(const char* s = "") {
        size_t n = strlen(s);
        data = new char[n + 1];
        strcpy(data, s);
    }

    Text(const Text& other) {
        size_t n = strlen(other.data);
        data = new char[n + 1];
        strcpy(data, other.data);
    }

    Text& operator=(const Text& other) {
        if (this != &other) {
            size_t n = strlen(other.data);
            char* temp = new char[n + 1];
            strcpy(temp, other.data);
            delete[] data;
            data = temp;
        }
        return *this;
    }

    ~Text() { delete[] data; }

    Text operator+(const Text& other) const {
        size_t n1 = strlen(data), n2 = strlen(other.data);
        char* temp = new char[n1 + n2 + 1];
        strcpy(temp, data);
        strcat(temp, other.data);
        Text result(temp);
        delete[] temp;
        return result;
    }

    bool operator==(const Text& other) const {
        return strcmp(data, other.data) == 0;
    }
    bool operator!=(const Text& other) const { return !(*this == other); }

    friend ostream& operator<<(ostream& out, const Text& t) {
        return out << t.data;
    }
};

int main() {
    Text a("Hello "), b("World"), c("");
    Text result = a + b + c;
    cout << result << '\n';
    Text copy = result;
    copy = copy;
    cout << boolalpha << (copy == result) << ' ' << (a != b) << '\n';
}
