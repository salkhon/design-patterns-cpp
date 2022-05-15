#pragma once

#include <string>

class PersonBuilder;
class PersonJobBuilder;
class PersonAddressBuilder;

class Person {
    // address
    std::string street_addr, post_code, city;

    // employment
    std::string company_name, position;
    int annual_income = 0;

public:
    static PersonBuilder create();

    friend class PersonBuilder;
    friend class PersonJobBuilder;
    friend class PersonAddressBuilder;

    friend std::ostream& operator<<(std::ostream& os, const Person& person);
};