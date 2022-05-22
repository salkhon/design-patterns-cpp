#include <iostream>
#include <string>
#include <memory>
#include <map>

using namespace std;

enum class Importance {
    primary, secondary, tertiary
};

template <typename T, typename Key = std::string>
class Multiton {
    static map<Key, shared_ptr<T>> instances;
    // when you call get() with a particular Key, you always get the value corresponding to the key. 

protected:
    Multiton() = default;

    virtual ~Multiton() = default;

public:
    static shared_ptr<T> get(const Key& key) {
        if (const auto iter = instances.find(key);
            iter != instances.end()) {
            return iter->second;
        } else {
            auto instance = make_shared<T>();
            instances[key] = instance;
            return instance;
        }
    }
};

template <typename T, typename Key>
map<Key, shared_ptr<T>> Multiton<T, Key>::instances;

class Printer {
    static int total_instance;
public:
    Printer() {
        ++Printer::total_instance;
        cout << "A total of " << Printer::total_instance << " instances created so far\n";
    }
};

int Printer::total_instance = 0;

int main() {
    typedef Multiton<Printer, Importance> mt;

    auto main = mt::get(Importance::primary);
    auto aux = mt::get(Importance::secondary);
    auto aux2 = mt::get(Importance::secondary);
}