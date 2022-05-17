#include <iostream>
#include <cmath>

using namespace std;

enum class PointType {
    cartesian, polar
};

struct Point {
    float x, y;

    // Point(float x, float y) : x(x), y(y) {}

    // suppose we want to initialize with polar coord
    // but constructor with arg float rho, float theta won't work, because overload of same type does not work. 

    Point(float a, float b, PointType type = PointType::cartesian) {
        if (type == PointType::cartesian) {
            x = a;
            y = b;
        } else {
            x = a * cos(b);
            y = a * sin(b);
        }
    }

    // problem, the arg names are too general to mean anything. Not good sanitazation of code. 

    // this is where factory method comes in. 
};

int main() {
    return 0;
}