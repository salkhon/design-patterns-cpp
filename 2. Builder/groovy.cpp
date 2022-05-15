#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct Tag {
    string name, text;
    vector<Tag> children;
    vector<pair<string, string>> attrs;

    friend ostream& operator<<(ostream& os, const Tag& tag) {
        os << "<" << tag.name;

        for (const auto& attr : tag.attrs) {
            os << " " << attr.first << "=\"" << attr.second << "\"";
        }

        if (tag.children.size() == 0 && tag.text.length() == 0) {
            os << "/>" << endl;
        } else {
            os << ">" << endl;

            if (tag.text.length()) {
                os << tag.text << endl;
            }

            for (const auto& child : tag.children) {
                os << child;
            }

            os << "</" << tag.name << ">" << endl;
        }

        return os;
    }

protected:
public:
    Tag(const string& name, const string& text) : name(name), text(text) {}
    Tag(const string& name, const vector<Tag>& children) : name(name), children(children) {}
};

struct P : Tag {
    P(const string& text) : Tag("p", text) {}
    P(initializer_list<Tag> children) : Tag("p", children) {}

};

struct IMG : Tag {
    IMG(const string& url) : Tag("img", "") {
        Tag::attrs.emplace_back(make_pair("src", url));
    }
};

int main() {
    cout <<
        P{
            IMG {
                "https://google.com"
            }
    }
    << endl;

    // taking a nesting of same type it, to make the nested init structure obvious through code. 

    // this allows you to contrain what elements go inside another element. 
    
    // for example, the IMG cannot contain anything else, therefore does not have a constructor taking
    // children. 
    return 0;
}