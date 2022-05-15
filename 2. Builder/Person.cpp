#include "Person.hpp"
#include "PersonBuilder.hpp"
#include <iostream>
#include <string>

using namespace std;

PersonBuilder Person::create() {
    return PersonBuilder();
}

ostream& operator<<(ostream& os, const Person& person) {
    os << "street_address: " << person.street_addr << " post_code: " << person.post_code <<
        " city: " << person.city << " company_name: " << person.company_name << " position: " << person.position <<
        " annual_income: " << person.annual_income;
    return os;
}