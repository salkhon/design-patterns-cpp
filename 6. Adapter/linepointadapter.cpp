#include <iostream>
#include <vector>
#include <memory>
#include "Geometry.hpp"

using namespace std;

vector<shared_ptr<VectorObject>> vectorObjects{
    make_shared<VectorRectangle>(10, 10, 100, 100),
    make_shared<VectorRectangle>(30, 30, 60, 60)
};

struct LineToPointAdapter {
    using Points = vector<Point>;

    LineToPointAdapter(Line& line) {
        int left = min(line.start.x, line.end.x);
        int right = max(line.start.x, line.end.x);
        int bottom = min(line.start.y, line.end.y);
        int top = max(line.start.y, line.end.y);

        int delx = right - left;
        int dely = top - bottom;

        if (delx == 0) {
            // vertical line
            for (int y = bottom; y <= top; y++) {
                points.push_back(Point{ left, y });
            }
        } else if (dely == 0) {
            // horizontal
            for (int x = left; x <= right; x++) {
                points.push_back(Point{ x, bottom });
            }
        } else {

        }
    }

    virtual Points::iterator begin() {
        return points.begin();
    }

    virtual Points::iterator end() {
        return points.end();
    }

private:
    Points points;
};

void draw_points(vector<Point>::iterator, vector<Point>::iterator);

void draw_shape_implementation(vector<VectorObject> shapes_madewithvectoroflines) {
    for (VectorObject& shape : shapes_madewithvectoroflines) {
        for (Line& line : shape) {
            LineToPointAdapter line_to_point_adapter(line);
            draw_points(line_to_point_adapter.begin(), line_to_point_adapter.end());
        }
    }
}

void draw_points(vector<Point>::iterator start, vector<Point>::iterator end) {
    // can only draw points
    for (auto iter = start; iter != end; iter++) {
        cout << "draw " << iter->x << ", " << iter->y << endl;
    }
}

int main() {

}