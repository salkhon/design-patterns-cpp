#include <iostream>
#include <string>
#include <ostream>
#include <memory>

#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

using namespace std;

struct Address {
    string street, city;
    int suite;

    Address(const string& street, const string& city, int suite) :
        street(street), city(city), suite(suite) {}

    Address(const Address& other) : street(other.street), city(other.city), suite(other.suite) {
        // further deep copy may be required if nested object has ptr attrs. 
    }

    friend ostream& operator << (ostream& os, const Address& address) {
        os << "street: " << address.street << " city: " << address.city << " suite: " << address.suite;
        return os;
    }
};

struct Contact {
    string name;
    shared_ptr<Address> address_ptr;

    Contact(const string& name, const shared_ptr<Address> address_ptr) : name(name), address_ptr(address_ptr) {}

    Contact(const Contact& other) : name(other.name), address_ptr(make_shared<Address>(*other.address_ptr)) {}

    friend ostream& operator << (ostream& os, const Contact& contact) {
        os << "name: " << contact.name << " address: " << *contact.address_ptr;
        return os;
    }
};

struct EmployeeFactory {
    static unique_ptr<Contact> new_main_office_employee(const string& name, const int suite) {
        // with default street, city from prototype
        static Contact p("", make_shared<Address>("123 East Dr", "London", 0));
        return new_employee(name, suite, p);
    }
private:
    static unique_ptr<Contact> new_employee(const string& name, const int suite, Contact& prototype) {
        auto result = make_unique<Contact>(prototype);
        result->name = name;
        result->address_ptr->suite = suite;
        return result;
    }
};

int main() {
    auto john = EmployeeFactory::new_main_office_employee("John", 123);
    // might make the Contact constructors private,and put employee factory inside Contact. 
    cout << *john << endl;

    return 0;
}