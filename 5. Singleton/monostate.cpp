#include <iostream>

class Printer {
    static int id;
    public:
    int get_id() const {
        return id;
    }

    void set_id(int value) {
        id = value;
    }
};

// for the consumer of the monostate design pattern, they are going to working with an ordinary type. 
// They will make instances of it. 
// behind the scenes, all of the storage is going to a static storage. 


int main() {
    Printer p;

    int id = p.get_id();

    Printer p2;

    // actually working with the same data. 

    //********* THIS IS A BAD IDEA. 

    // Inheritance will not work. You effectively have the members as NON-inheritable.
    // You cannot inherit static attrs. 
    // Really inflexible. 

    // Worst issue is: The client is not informed about Singleton. 



    return 0;
}