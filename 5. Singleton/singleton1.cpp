#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <map>

using namespace std;

class SingletonDatabase {
    map<string, int> capitals;

    SingletonDatabase() {
        cout << "Initializing database\n";

        ifstream ifs("capitals.txt");

        string s1, s2;

        while (getline(ifs, s1)) {
            getline(ifs, s2);
            int population = stoi(s2);
            capitals[s1] = population;
        }
    }

public:
    SingletonDatabase(SingletonDatabase const& singletondb) = delete;
    void operator = (SingletonDatabase const& singletondb) = delete;
    // this ensures nobody can replicate the database in any way. 

    // access the singleton
    static SingletonDatabase& get() {
        static SingletonDatabase db;
        return db;
    }

    int get_population(const string& name) {
        return this->capitals[name];
    }
};

int main() {
    // auto db = SingletonDatabase::get();
    // CAN't DO THIS BECAUSE ASSIGN IS NOT ALLOWED!!!

    string city = "Dhaka";
    cout << city << " has population of " <<
        SingletonDatabase::get().get_population("Dhaka");

    return 0;
}