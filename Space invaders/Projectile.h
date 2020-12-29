#pragma once

#include <memory>
#include "Rectangle.h"

class Renderer;
class Projectile {
public:
    Projectile(int posX, const std::shared_ptr<Renderer>& renderer);
    void Move(int speed);
    void Draw();
private:
    Rectangle m_rect;
};
