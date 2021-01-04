#pragma once

#include <memory>
#include "Rectangle.h"

class Renderer;
class Projectile {
public:
    Projectile(float posX, float posY, const std::shared_ptr<Renderer>& renderer);
    void Move(float speed);
    void Draw();
    void SetXPos(float pos) noexcept;
    void SetPos(float xPos, float yPos) noexcept;
    Rectangle& GetRectangle() { return m_rect; }
private:
    Rectangle m_rect;
};
