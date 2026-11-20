#include <iostream>
using namespace std;

struct Person {
    Person() { cout << "Person "; }
    string name = "PersonName";
};
struct Student : Person {
    Student() { cout << "Student "; }
};
struct Staff : Person {
    Staff() { cout << "Staff "; }
};
struct TeachingAssistant : Student, Staff {
    TeachingAssistant() { cout << "TA "; }
};

int main() {
    TeachingAssistant ta;
    cout << "\nPerson subobjects: two\n";
    // cout << ta.name; // Uncomment to see ambiguity: two Person::name members.
    cout << ta.Student::name << " " << ta.Staff::name << '\n';
}
