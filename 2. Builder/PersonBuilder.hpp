#pragma once
#include "Person.hpp"

class PersonJobBuilder;
class PersonAddressBuilder;

class PersonBuilderBase {
protected:
    Person& person;

    PersonBuilderBase(Person& person) : person(person) {}

public:
    // to move the Person object after the last builder is done. 
    operator Person () const {
        return std::move(this->person);
    }
    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;
};

// PersonBuilder is the host for the Person object that is created. 
class PersonBuilder : public PersonBuilderBase {
    Person p;
public:
    PersonBuilder() : PersonBuilderBase(p) {}
};