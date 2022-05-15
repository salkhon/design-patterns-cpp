#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class HtmlElement;
struct HtmlBuilder;

class HtmlElement {
    friend class HtmlBuilder;

    string name, text;
    vector<HtmlElement> children;

    const size_t indent_size = 2;

    HtmlElement() {}

    HtmlElement(const string& name, const string& text) : name(name), text(text) {}

public:
    string str(int indentation_level = 0) const {
        ostringstream oss;
        string indent(indent_size * indentation_level, ' ');
        oss << indent << "<" << name << ">" << endl;

        if (this->text.size() > 0) {
            oss << string(indent_size * (indentation_level + 1), ' ') << text << endl;
        }

        for (const auto& child : this->children) {
            oss << child.str(indentation_level + 1);
        }

        oss << indent << "</" << name << ">" << endl;
        return oss.str();
    }

    static HtmlBuilder build(string root_name) {
        return {root_name};
    }
};

struct HtmlBuilder {
    HtmlElement root;

    HtmlBuilder(string root_name) {
        this->root.name = root_name;
    }

    HtmlBuilder& add_child(string child_name, string child_text) {
        HtmlElement htmlElem(child_name, child_text);
        this->root.children.emplace_back(htmlElem);
        return *this;
    }

    string str() const {
        return this->root.str();
    }

    HtmlElement create() {
        return this->root;
    }
};

int main() {
    auto text = "hello";
    string output;
    output += "<p>";
    output += text;
    output += "</p>";
    cout << output << endl;
    // this approach does not really scale

    string words[] = { "hello", "world" };
    ostringstream oss;
    oss << "<ul>";

    for (auto w : words) {
        oss << " <li>" << w << "</li>";
    }

    oss << "</ul>";

    cout << oss.str() << endl;
    // better but still concatenating strings. 

    // OOP builder
    HtmlElement html_elem = HtmlElement::build("ul")
        .add_child("li", "Hello")
        .add_child("li", "World")
        .create();

    cout << html_elem.str() << endl;

    // we're doing this with a special dedicated component. Instead of working directly with the 
    // HTML element, we're avoiding it by creating a dedicated component. Using a specialized component
    // which has the specialized functions to help you create the object. 

    return 0;
}