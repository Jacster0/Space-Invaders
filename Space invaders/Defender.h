#pragma once
//This is the guy which will defend against the invaders
#include "Rectangle.h"
#include "Projectile.h"

class Renderer;
class SDL_Texture;
class Defender {
public:
    Defender(const std::shared_ptr<Renderer>& renderer);
    ~Defender();

    void Move(float step);
    void Draw();
    void Shoot() noexcept;
    void ResetProjectile();
    void ResetHit();
    void Reset();
    std::shared_ptr<Projectile> GetProjectile() const noexcept;
    bool GetProjectileIsLaunched() const noexcept;
    const Rectangle& GetRectangle() const noexcept;

    void Hit() noexcept;
    bool IsHit() const noexcept;
private:
    Rectangle m_rect;
    std::shared_ptr<Projectile> m_projectile;
    std::shared_ptr<Renderer> m_renderer;

    SDL_Texture* m_defenderTexture = nullptr;

    bool m_projectileIsLaunched = false;
    bool m_isHit = false;
};