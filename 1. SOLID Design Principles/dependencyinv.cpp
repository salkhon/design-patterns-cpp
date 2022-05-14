#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <tuple>

using namespace std;

enum class Relationship {
    parent, child, sibling
};

struct Person {
    string name;

};

struct RelationshipBrowser {
    virtual vector<Person> find_all_children_of(const string& name) = 0;
};

// low level module / construct
// all it does is provide functionality for data storage
struct Relationships : RelationshipBrowser {
    vector<tuple<Person, Relationship, Person>> relations;

    void add_parent_and_child(const Person& parent, const Person& child) {
        relations.push_back({ parent, Relationship::parent, child }); // implicit tuple initializer
        relations.push_back({ child, Relationship::child, parent });
    }

    vector<Person> find_all_children_of(const string& name) override {
        // now the high level module is directly dependent on the implementation details. 
        vector<Person> result;
        for (auto& tup : this->relations) {
            auto& first = get<0>(tup);
            auto& rel = get<1>(tup);
            auto& second = get<2>(tup);
            if (first.name == "John" && rel == Relationship::parent) {
                result.push_back(second);
            }
        }
        return result;
    }

};

// if you want to perform research on the low level module, that would be called
// a high level module
struct Research {
    Research(Relationships& relationships) {
        // VIOLATES PRINCIPLE
        // HIGHER LEVEL MODULE DEPENDING ON LOWER LEVEL Relationships module.
        auto& relations = relationships.relations;
        // now the high level module is directly dependent on the implementation details. 
        for (auto& tup : relations) {
            auto& first = get<0>(tup);
            auto& rel = get<1>(tup);
            auto& second = get<2>(tup);
            if (first.name == "John" && rel == Relationship::parent) {
                cout << "John has a child called " << second.name << endl;
            }
        }
    }

    // if the low level module decides to make the relations attribute PRIVATE, or changes the 
    // storage nature of the relations, then our implementation would break. 

    // So the dependency inversion principle, saves you from changes in the implementation
    // detail. 

    // This can be solved by inheriting our low level Relatinoships from an abstract class that
    // provides a handle for the functionality of checking someone'e children. 
    // And Relationships internally provides that implementation for you. 
};

struct ResearchFIXED {
    ResearchFIXED(RelationshipBrowser& relationship_browser) {
        for (auto& child : relationship_browser.find_all_children_of("John")) {
            cout << "John has a child called " << child.name << endl;
        }
    }
};



int main() {
    Person parent{ "John" };
    Person child1{ "Chris" }, child2{ "Matt" };

    Relationships relationships;
    relationships.add_parent_and_child(parent, child1);
    relationships.add_parent_and_child(parent, child2);

    Research _(relationships);
    ResearchFIXED _1(relationships);

    return 0;
}