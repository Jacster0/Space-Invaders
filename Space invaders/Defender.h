#pragma once
//This is the guy which will defend against the invaders
#include "Rectangle.h"
#include "Projectile.h"

class Renderer;
class Defender {
public:
    Defender(const std::shared_ptr<Renderer>& renderer);
    void Move(int speed);
    void Draw();
    void Shoot();
private:
    std::unique_ptr<Projectile> m_projectile;
    Rectangle rect;
    std::shared_ptr<Renderer> m_renderer;
};