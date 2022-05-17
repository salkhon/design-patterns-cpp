#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <math.h>
#include <ostream>

using namespace std;

enum class PointType {
    cartesian, polar
};

struct PointFactory;

class Point {
    friend class PointFactory; // VIOLATES OPEN-CLOSE PRINCIPLE. 
    // We've changed an already written class. 

    // as an alternative, make everything public. As a result, PointFactory can coexist without content
    // modification of class Point.

    // to avoid this, we nest the PointFactory inside Point.  

    float x, y;
public:
    // allows the use of constructor, USED INTERNALLY. 

    friend ostream& operator << (ostream& os, const Point& point) {
        os << "x: " << point.x << " y: " << point.y;
        return os;
    }

    struct PointFactory {
        static Point NewCartesian(float x, float y) {
            return Point(x, y);
        }

        static Point NewPolar(float r, float theta) {
            return Point(r * cos(theta), r * sin(theta));
        }
    };

private:
    Point(float x, float y) : x(x), y(y) {}
};

struct PointFactory {
    static Point NewCartesian(float x, float y) {
        return Point(x, y);
    }

    static Point NewPolar(float r, float theta) {
        return Point(r * cos(theta), r * sin(theta));
    }
};

int main() {
    auto p = PointFactory::NewPolar(5, M_PI);

    cout << p << endl;

    auto p1 = Point::PointFactory::NewPolar(5, M_PI);

    cout << p1 << endl;

    // this is better, if someone comes to Point, they see the inner class, they see the API and 
    // mode intuitive to figure out what's going on. 


    return 0;
}