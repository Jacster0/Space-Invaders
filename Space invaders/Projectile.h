#pragma once

#include <memory>
#include "Rectangle.h"

class Renderer;
class Projectile {
public:
    Projectile(float posX, float posY, const std::shared_ptr<Renderer>& renderer);
    void Move(int speed);
    void Draw();
    void SetXPos(float pos) noexcept;
    Rectangle& GetRectangle() { return m_rect; }
private:
    Rectangle m_rect;
};
