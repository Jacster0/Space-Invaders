#include "Shape.h"
#include <iostream>

Shape::Shape(Point2D point, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    :
    point(point)
{
    color = a << 24 | r << 16 | g << 8 | b;
}

uint8_t Shape::GetAlpha() const {
    return (color >> 24) & 0xFF;
}

uint8_t Shape::GetRed() const {
    return (color >> 16) & 0xFF;
}

uint8_t Shape::GetGreen() const {
    return (color >> 8) & 0xFF;
}

uint8_t Shape::GetBlue() const {
    return color & 0xFF;
}

Point2D Shape::GetPoint() const {
    return point;
}

void Shape::SetAlpha(uint8_t value) {
    if (value < 0 || value > 255) {
        std::cout << "Value must be between 0 and 255!" << std::endl;
        return;
    }
    color = (color & 0x00FFFFFF) | (value << 24);
}

void Shape::SetRed(uint8_t value) {
    if (value < 0 || value > 255) {
        std::cout << "Value must be between 0 and 255!" << std::endl;
        return;
    }
    color = (color & 0xFF00FFFF) | (value << 16);
}

void Shape::SetGreen(uint8_t value) {
    if (value < 0 || value > 255) {
        std::cout << "Value must be between 0 and 255!" << std::endl;
        return;
    }
    color = (color & 0xFFFF00FF) | (value << 8);
}

void Shape::SetBlue(uint8_t value) {
    if (value < 0 || value > 255) {
        std::cout << "Value must be between 0 and 255!" << std::endl;
        return;
    }
    color = (color & 0xFFFFFF00) | value;
}

void Shape::SetPoint(Point2D point) {
    this->point = point;
}
