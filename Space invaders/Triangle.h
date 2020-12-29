#pragma once
#include "Shape.h"
#include <memory>

//Using forward declarations to keep the header files clean
class Renderer;
class Triangle : public Shape {
    Triangle(Point2D point, uint8_t r, uint8_t g, uint8_t b, uint8_t a, int base, int height);

    int GetBase() const;
    int GetHeight() const;
    void SetBase(int value);
    void SetHeight(int value);

    void render(RenderFlags renderFlags) override;
private:
    std::shared_ptr<Renderer> m_renderer;
    int base;
    int height;
};