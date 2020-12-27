#include "Rectangle.h"
#include "Renderer.h"
#include <iostream>

Rectangle::Rectangle(Point2D point, uint8_t r, uint8_t g, uint8_t b, uint8_t a, int width, int height)
    :
    Shape(point, r, g, b, a),
    width(width),
    height(height)
{}

int Rectangle::GetWidth() const {
    return width;
}

int Rectangle::GetHeight() const {
    return height;
}

void Rectangle::SetWidth(int value) {
    if (value < 0) {
        std::cout << "Width cannot be negative!" << std::endl;
        return;
    }
    width = value;
}

void Rectangle::SetHeight(int value) {
    if (value < 0) {
        std::cout << "Height cannot be negative!" << std::endl;
        return;
    }
    height = value;
}

void Rectangle::render(Renderer* renderer) {
    std::cout << "Rectangle" << std::endl;
    std::cout << "Position:" << std::endl;
    std::cout << GetPoint().to_string() << std::endl;
    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;

    Point2D pt = GetPoint();
    //set the color
    renderer->SetColor(GetRed(), GetGreen(), GetBlue(), GetAlpha());
    //calculate the start and end screen coords
    int startX = pt.x;
    int endX = pt.x + width;

    int startY = pt.y;
    int endY = pt.y + height;

    //draw the outline of the shape
    //Horizontal lines
    renderer->DrawLine(Point2D(startX, startY), Point2D(endX, endY));
    renderer->DrawLine(Point2D(startX, endY), Point2D(endX, endY));
   
    //vertical lines
    renderer->DrawLine(Point2D(startX, startY), Point2D(startX, endY));
    renderer->DrawLine(Point2D(endX, startY), Point2D(endX, endY));
}
