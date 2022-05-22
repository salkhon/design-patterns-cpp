#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <map>
#include <vector>

using namespace std;

class Database {
public:
    virtual int get_population(const string& name) = 0;
};

class SingletonDatabase : public Database {
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

    static SingletonDatabase& get() {
        static SingletonDatabase db;
        return db;
    }

    int get_population(const string& name) override {
        return this->capitals[name];
    }
};

class DummyDatabase : public Database {
    map<string, int> capitals;

public:
    DummyDatabase() {
        this->capitals["alpha"] = 1;
        this->capitals["beta"] = 2;
        this->capitals["gamma"] = 3;
    }

    int get_population(const string& name) override {
        return this->capitals[name];
    }
};

struct SingletonRecordFinder {
    int total_population(vector<string> names) {
        int result = 0;

        for (auto& name : names) {
            result += SingletonDatabase::get().get_population(name);
        }
    }
};

// problem occurs when you want to test SingletonRecordFinder. 

// testing is strongly tied to the database. 
// THEREFORE, it's not a unit test!!
// It tests SingletonRecordFinder. But to do so, it needs the Singleton database to work as well.
// Due to the strong coupling due to the singleton database itself, we are unable to decouple them. 

// This is dangerous. Becuase at some point the database might change. Which will break the test
// of SingletonRecordFinder. 

// Rather to inject the depdendency instead having sealed as the Singleton db, we provide the Singleton db
// an interface. Particularly the method we are using: get_population(). 
// Depenedncy injection on the subject to unit test, of the coupled singleton. 

struct ConfigurableRecordFinder {
    Database& db; // interfacing the Singleton db

    ConfigurableRecordFinder(Database& db) : db(db) {}

    int total_population(vector<string> names) {
        int result = 0;

        for (auto& name : names) {
            result += db.get_population(name);
        }
    }
};

TEST(RecorrdFinderTests, DependentTotalPopulationTest) {
    DummyDatabase db;
    ConfigurableRecordFinder rf(db);
    EXPECT_EQ(4, rf.total_population({ "alpha", "gamma" }));
}

// So singleton itself is not a bad idea, it's bad if you have a HARD DEPENDENCY on it. 

int main() {
    string city = "Dhaka";
    cout << city << " has population of " <<
        SingletonDatabase::get().get_population("Dhaka");

    return 0;
}