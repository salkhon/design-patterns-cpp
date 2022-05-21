#include <iostream>
#include <string>
#include <ostream>

using namespace std;

struct Address {
    string street, city;
    int suite;

    Address(const string& street, const string& city, int suite) :
        street(street), city(city), suite(suite) {}

    friend ostream& operator << (ostream& os, const Address& address) {
        os << "street: " << address.street << " city: " << address.city << " suite: " << address.suite;
        return os;
    }
};

struct Contact {
    string name;
    Address address;

    Contact(const string& name, const Address& address) : name(name), address(address) {}

    friend ostream& operator << (ostream& os, const Contact& contact) {
        os << "name: " << contact.name << " address: " << contact.address;
        return os;
    }
};

int main() {
    Contact john("John Doe", Address("123 East Dr", "London", 123));
    Contact jane("Jane Smith", Address("123 East Dr", "London", 103));
    // maybe make a single prototype which has the correct address, and make copies. 
    Contact janefromjohn = john;
    janefromjohn.name = "Jane Smith";
    janefromjohn.address.suite = 103;

    cout << john << endl << janefromjohn;

    // but most implementations don't keep all values as values. 
    // they keep a pointer. 
    // they don't work the way as value. 
    
    return 0;
}