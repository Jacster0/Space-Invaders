#pragma once
//This is the guy which will defend against the invaders
#include "Rectangle.h"
#include "Projectile.h"

class Renderer;
class Defender {
public:
    Defender(const std::shared_ptr<Renderer>& renderer);
    void Move(float speed);
    void Draw();
    void Shoot() noexcept;
    void ResetProjectile();
    std::shared_ptr<Projectile> GetProjectile() const noexcept;
    bool GetProjectileIsLaunched() const noexcept;
    const Rectangle& GetRectangle() const noexcept;
private:
    Rectangle m_rect;
    std::shared_ptr<Projectile> m_projectile;
    std::shared_ptr<Renderer> m_renderer;
    bool m_projectileIsLaunched = false;
};