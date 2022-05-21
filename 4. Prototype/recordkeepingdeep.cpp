#include <iostream>
#include <string>
#include <ostream>
#include <memory>

using namespace std;

struct Address {
    string street, city;
    int suite;

    Address(const string& street, const string& city, int suite) :
        street(street), city(city), suite(suite) {}

    Address(const Address& other) : street(other.street), city(other.city), suite(other.suite) {}

    friend ostream& operator << (ostream& os, const Address& address) {
        os << "street: " << address.street << " city: " << address.city << " suite: " << address.suite;
        return os;
    }
};

struct Contact {
    string name;
    shared_ptr<Address> address_ptr;

    Contact(const string& name, const shared_ptr<Address> address) : name(name), address_ptr(address) {}

    // Contact(const Contact& other) : name(other.name),
    //     address(make_shared<Address>(other.address->street, other.address->city, other.address->suite)) {
    //     // deep copying constructor
    //     // BUT ONLY WORKS IF ADDRESS has only value attrs. 

    //     // SHOULD DEEP COPY ADDRESS AS WELL
    // }

    Contact(const Contact& other) : name(other.name), address_ptr(make_shared<Address>(*other.address_ptr)) {}

    friend ostream& operator << (ostream& os, const Contact& contact) {
        os << "name: " << contact.name << " address: " << *contact.address_ptr;
        return os;
    }
};

int main() {
    Contact john("John Doe", make_shared<Address>("123 East Dr", "London", 123));
    Contact jane("Jane Smith", make_shared<Address>("123 East Dr", "London", 103));

    Contact janefromjohn = john;
    janefromjohn.name = "Jane Smith";
    janefromjohn.address_ptr->suite = 103;

    cout << john << endl << janefromjohn;

    return 0;
}