#include <iostream>
#include <string>
using namespace std;

class Person {
public:
    string name;
    int id;
    Person(string n, int i) : name(n), id(i) {}
};
class Student {
public:
    Person person;
    string programme;
    Student(string n, int i, string p) : person(n, i), programme(p) {}
};
class Staff {
public:
    Person person;
    string department;
    Staff(string n, int i, string d) : person(n, i), department(d) {}
};
class TeachingAssistant {
public:
    Student student;
    Staff staff;
    TeachingAssistant(string n, int i)
        : student(n, i, "CSE"), staff(n, i, "IT") {}
};

int main() {
    TeachingAssistant ta("Kiran", 11);
    cout << ta.student.person.name << " " << ta.staff.person.name << '\n';
}
