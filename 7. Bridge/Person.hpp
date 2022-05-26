#pragma once
#include <string>
#include <iostream>

using namespace std;

class Person {
public:
    string name;

    class PersonImpl;
    // Person implementation is hidden

    PersonImpl* impl;

    Person();
    ~Person();

    void greet();
};
