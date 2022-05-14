#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Journal {
    string title;
    vector<string> entries;

    Journal(const string& title) : title(title) {}

    void add_entry(const string& entry) {
        static int count = 1;
        entries.push_back(to_string(count++) + ": " + entry);
    }
};

struct PersistenceManager {
    static void save(const Journal& j, const string& filename) {
        ofstream ofs(filename);
        for (auto& e : j.entries) {
            ofs << e << endl;
        }
    }
};

int main() {
    Journal journal("Dear Diary");
    journal.add_entry(" I ate a bug");
    journal.add_entry("I cried today");

    // to save the journal into a file, 
    // don't add the saving functionality in the Journal. That's not a part of the Journal. 
    // Separate concern of persistence in your journal. 
    // When you want to change Persistence, you have to change in multiple places. 

    // So we do: separation of concerns. 
    // Journal should take care of the journal only. 
    // Persisting should have a separate function, or class. 

    PersistenceManager pm;
    pm.save(journal, "diary.txt");
    return 0;
}
