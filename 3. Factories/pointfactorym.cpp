#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <math.h>
#include <ostream>

using namespace std;

enum class PointType {
    cartesian, polar
};

class Point {
public:
    float x, y;

    static Point NewCartesian(float x, float y) {
        return Point(x, y);
    }

    static Point NewPolar(float r, float theta) {
        return Point(r * cos(theta), r * sin(theta));
    }

    // allows the use of constructor, USED INTERNALLY. 

    friend ostream& operator << (ostream& os, const Point& point) {
        os << "x: " << point.x << " y: " << point.y;
        return os;
    }

private:
    Point(float x, float y) : x(x), y(y) {}

};

int main() {
    auto p = Point::NewPolar(5, M_PI);
    cout << p << endl;
    return 0;
}