#include "Person.hpp"

class Person::PersonImpl {
    public:
    void greet(Person* person) {

    }
};

// not implementing in a header file - so whoever is consuming the header file is not exposed to the detail
// of the implementation. 

void Person::PersonImpl::greet(Person* p) {
    cout << "hello my name is " << p->name << endl;
}
// hidden implementation of a method. The actual method will just relay to this implementation. 

Person::Person() : impl(new PersonImpl()) {

}

Person::~Person() {
    delete impl;
}

void Person::greet() {
    impl->greet(this);
}