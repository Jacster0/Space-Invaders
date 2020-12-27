#pragma once

#include <string>

class Point2D {
public:
    Point2D();
    Point2D(float x, float y);
    Point2D(const Point2D& rhs);
    Point2D& operator=(const Point2D& rhs);

    Point2D operator+(const Point2D& rhs);
    bool operator==(const Point2D& rhs);

    float distance(const Point2D& point) const;
    std::string to_string() const;

    float x;
    float y;
};