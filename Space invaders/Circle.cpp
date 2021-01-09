#include "Circle.h"
#include "Renderer.h"
#include <iostream>

Circle::Circle(Point2D point, int radius)
    :
    Shape(point, 0u, 0u, 0u, 1u),
    radius(radius)
{}

int Circle::GetRadius() const {
    return radius;
}

void Circle::SetRadius(int value) {
    if (value < 0) {
        std::cout << "Radius cannot be negative!" << std::endl;
        return;
    }
    radius = value;
}

void Circle::render(RenderFlags renderFlags) {
    if ((renderFlags & RenderFlag::Fill) == RenderFlag::Fill) {
        throw std::exception("Circle does not support the Renderflag::Fill mode");
    }

    Point2D pt = GetPoint();
    //set the color
    m_renderer->SetColor(GetRed(), GetGreen(), GetBlue(), GetAlpha());

    int theta = 0;

    while (theta++ <= 360) {
        int x = GetRadius() * cos(theta);
        int y = GetRadius() * sin(theta);

        int screenPosX = x + pt.x;
        int screenPosY = y + pt.y;

        m_renderer->DrawLine(Point2D(screenPosX, screenPosY), Point2D(screenPosX, screenPosY));
    }
}

