#include "Triangle.h"
#include "Renderer.h"
#include <iostream>

Triangle::Triangle(Point2D point, uint8_t r, uint8_t g, uint8_t b, uint8_t a, int base, int height)
    :
    Shape(point, r, g, b, a),
    base(base),
    height(height)
{
}

int Triangle::GetBase() const {
    return base;
}

int Triangle::GetHeight() const {
    return height;
}

void Triangle::SetBase(int value) {
    if (value < 0) {
        std::cout << "Base cannot be negative!" << std::endl;
        return;
    }
    base = value;
}

void Triangle::SetHeight(int value) {
    if (value < 0) {
        std::cout << "Height cannot be negative!" << std::endl;
        return;
    }
    height = value;
}

void Triangle::render(RenderFlags renderFlags) {
    std::cout << "Triangle" << std::endl;
    std::cout << "Position:" << std::endl;
    std::cout << GetPoint().to_string() << std::endl;
    std::cout << "Base: " << base << std::endl;
    std::cout << "Height: " << height << std::endl;

    Point2D pt = GetPoint();
    //set the color
    m_renderer->SetColor(GetRed(), GetGreen(), GetBlue(), GetAlpha());

    //calculate the start and end screen coords
    int startX = pt.x;
    int endX = pt.x + base;

    int halfBase = base / 2;
    int middle = halfBase + pt.x;

    int startY = pt.y;
    int endY = pt.y + height;
    //Draw the base
    m_renderer->DrawLine(Point2D(startX, startY), Point2D(endX, startY));

    //Draw the diagonal lines
    m_renderer->DrawLine(Point2D(pt.x, startY), Point2D(middle, endY));
    m_renderer->DrawLine(Point2D(middle, endY), Point2D(endX, startY));
}
