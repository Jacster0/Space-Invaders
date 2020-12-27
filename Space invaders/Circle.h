#pragma once
#include "Shape.h"

//Using forward declarations to keep the header files clean
struct SDL_Renderer;
class Circle : public Shape {
public:
    Circle(Point2D point, int radius);
public:
    int GetRadius() const;
    void SetRadius(int value);
public:
    void render(SDL_Renderer* renderer) override;
private:
    int radius;
};

