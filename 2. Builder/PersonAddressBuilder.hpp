#pragma once
#include <string>

class PersonAddressBuilder : public PersonBuilderBase {
public:
    PersonAddressBuilder(Person& person) : PersonBuilderBase(person) {}

    PersonAddressBuilder& at(std::string street_address) {
        PersonBuilderBase::person.street_addr = street_address;
        return *this;
    }

    PersonAddressBuilder& with_postcode(std::string post_code) {
        PersonBuilderBase::person.post_code = post_code;
        return *this;
    }

    PersonAddressBuilder& in(std::string city) {
        PersonBuilderBase::person.city = city;
        return *this;
    }
};