#include "Point2D.h"

Point2D::Point2D()
    :
    x(0.0f),
    y(0.0f)
{}

Point2D::Point2D(float x, float y)
    :
    x(x),
    y(y)
{}

Point2D::Point2D(const Point2D& rhs) {
    x = rhs.x;
    y = rhs.y;
}

Point2D& Point2D::operator=(const Point2D& rhs)
{
    x = rhs.x;
    y = rhs.y;
    return *this;
}

Point2D Point2D::operator+(const Point2D& rhs) {
    Point2D point;

    point.x = x + rhs.x;
    point.y = y + rhs.y;
    return point;
}

bool Point2D::operator==(const Point2D& rhs) {
    return x == rhs.x && y == rhs.y;
}

float Point2D::distance(const Point2D& point) const {
    auto distX = x - point.x;
    auto distY = y - point.y;

    return sqrt(pow(distX, 2) + pow(distY, 2));
}

std::string Point2D::to_string() const {
    return "[" + std::to_string(x) + ", " + std::to_string(y) + "]";
}