#include "headers.hpp"

// Shapes - circle, square
// Renderer - raster, vector. 

// 2x2 RasterCircleRenderer, RasterSquareRendered, VectorCirleRend. ...
using namespace std;

struct Renderer {
    virtual void render_circle(float x, float y, float radius) = 0;
};

struct VectorRenderer : Renderer {
    void render_circle(float x, float y, float radius) override {
        cout << "Drawing a vector circle of radius " << radius << endl;
    }
};

struct RasterRenderer : Renderer {
    void render_circle(float x, float y, float radius) override {
        cout << "Rasterizing a circle of radius " << radius << endl;
    }
};

struct Shape {
    // bridge to the rendered that is being applied to the shape. 
protected:
    Renderer& renderer;

    Shape(Renderer& renderer) : renderer(renderer) {}

public:
    virtual void draw() = 0;
    virtual void resize(float factor) = 0;
};

struct Circle : Shape {
    float x, y, radius;
     
    Circle(Renderer& renderer, float x, float y, float radius)
        : Shape(renderer), x(x), y(y), radius(radius) {}

    void draw() override {
        renderer.render_circle(x, y, radius);
    }

    void resize(float factor) override {
        radius *= factor;
    }
};

// in a cartesian product like situation one aspect of the entities might be more explicit to the client
// naturally than the other. So we form the class hierarchy (inheritance) on that aspect, and aggregate
// the other aspect inside that main inheritance hierarchy, as an interface. That internal implementation
// is one level hidden away. 

int main() {
    return 0;
}