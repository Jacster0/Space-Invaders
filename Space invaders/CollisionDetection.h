#pragma once
#include "Rectangle.h"

class CollisionDetection {
public:
    CollisionDetection() = default;
    bool CheckCollison(const Rectangle& firstRectangle, const Rectangle& secondRectangle);
};