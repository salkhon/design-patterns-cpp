#pragma once

#include <vector>

struct Point {
    int x, y;
};

struct Line {
    Point start, end;
};

struct VectorObject {
    virtual std::vector<Line>::iterator begin();
    virtual std::vector<Line>::iterator end();
};

struct VectorRectangle : VectorObject {
    VectorRectangle(int x, int y, int width, int height)
        : lines{
            Line{Point{x, y}, Point{x + width, y}},
            Line{Point{x + width, y}, Point{x + width, y + height}},
            Line{Point{x + width, y + height}, Point{x, y + height}},
            Line{Point{x, y + height}, Point{x, y}}
    } {}
private:
    std::vector<Line> lines;
};