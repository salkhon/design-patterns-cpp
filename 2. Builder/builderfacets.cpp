#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Person.hpp"
#include "PersonBuilder.hpp"
#include "PersonAddressBuilder.hpp"
#include "PersonJobBuilder.hpp"

using namespace std;

int main() {
    Person p = Person::create()
        .lives().at("123 London Road").with_postcode("SW1 1GB").in("London")
        .works().at("PragmaSoft").as_a("Consultant").earning(10e6);
    // builder facede. 
    // have the base builedr jump from one builder to another builder. 
    // have a sub builder that hosts the object being built. 
    // other subbuilders refer to that builder. 
    cout << p;
    return 0;
}