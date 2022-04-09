#include "StdList.h"

class Person {
private:
    std::string firstName;
    std::string lastName;
public:
    Person(const std::string& f, const std::string& l) : firstName(f), lastName(l) {}
    std::string getFirstName() const {return firstName;}
    std::string getLastName() const {return lastName;}   

    bool operator < (const Person& p) const;
    friend std::ostream& operator <<(std::ostream& out, const Person& p); 
};

bool Person::operator < (const Person& p) const {
    // const Person& p blir høyre side av < tegnet, sjekker om det andre objektet er før i alfabetet
    return (lastName + firstName) < (p.lastName + p.firstName);
}

std::ostream& operator <<(std::ostream& out, const Person& p){
    out << p.lastName << ", " << p.firstName;
    return out;
}

void insertOrdered(std::list<Person> &l, const Person& p) {
    for (auto pit = l.begin(); pit != l.end(); ++pit) {
        if (p < *pit) {
            l.insert(pit, p); // setter inn person på funnet posisjon
            return;
        } 
    }
    l.push_back(p); // hvis ingen elementer er større, setter inn på slutten
}

void testStdLists() {
    std::cout << "std::list:\n";

    std::list<Person> people;
    insertOrdered(people, Person("Rebekka", "Olsen"));
    insertOrdered(people, Person("Sander", "Antun"));
    insertOrdered(people, Person("Stig", "Brenner"));
    insertOrdered(people, Person("Lars", "Brenner"));

    for (const auto& p : people) {
        std::cout << p << '\n';
    }

    std::cout << '\n';
}

