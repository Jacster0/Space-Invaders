#pragma once
#include "Shape.h"

//Using forward declarations to keep the header files clean
struct SDL_Renderer;
class Triangle : public Shape {
public:
    Triangle(Point2D point, uint8_t r, uint8_t g, uint8_t b, uint8_t a, int base, int height);
public:
    int GetBase() const;
    int GetHeight() const;
    void SetBase(int value);
    void SetHeight(int value);
public:
    void render(SDL_Renderer* renderer) override;
private:
    int base;
    int height;
};