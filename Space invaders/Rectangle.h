#pragma once
#include "Shape.h"
#include <memory>

//Using forward declarations to keep the header files clean
class Renderer;
class Rectangle : public Shape {
public:
    Rectangle(Point2D point, uint8_t r, uint8_t g, uint8_t b, uint8_t a, int width, int height, std::shared_ptr<Renderer> renderer);
    int GetWidth() const;
    int GetHeight() const;
    void SetWidth(int value);
    void SetHeight(int value);

    //Renders the Rectangle onto the screen
    void render(RenderFlags renderFlags) override;
private:
    std::shared_ptr<Renderer> m_renderer;
    int width;
    int height;
};