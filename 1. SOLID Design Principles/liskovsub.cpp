#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Rectangle {
protected:
    int width, height;
public:
    Rectangle(int width, int height) : width(width), height(height) {}

    int get_width() const {
        return width;
    }

    virtual void set_width(int width) {
        this->width = width;
    }

    int get_height() const {
        return height;
    }

    virtual void set_height(int height) {
        this->height = height;
    }

    int area() const {
        return width * height;
    }
};

class Square : public Rectangle {
public:
    Square(int size) : Rectangle(size, size) {}

    void set_width(int width) override {
        this->width = this->height = width;
    }

    void set_height(int height) override {
        this->width = this->height = height;
    }

    // we've violated the Liskov Substitution Principle. 
    // process() does something different for Square than it dos for Rectangle.
    // we've broken the setters. 
};

void process(Rectangle& rec) {
    int w = rec.get_width();
    rec.set_height(10);

    cout << "expected area = " << (w * 10) << ", got " << rec.area() << "\n";
}

struct RectangleFactory {
    static Rectangle create_rectanngle(int w, int h);
    static Rectangle create_square(int size);
};

int main(){
    Rectangle rec(3, 4);
    process(rec);

    Square sq(5);
    process(sq); // sets the height like rectangle,
    // unlike rectangle, also sets the same to width. 

    // Idea: the inheritance of square from rectangle is not sound. 
    // Square has different behavior when it comes to disntinguishing between h and w. 

    // We could use a factory class, that generates Rectangles that are also squares.
    // You should be able to substitute a child class (square) into any location where a base class
    // rectangle is begin used.  
    return 0;
}