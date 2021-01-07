#pragma once
#include "Rectangle.h"
#include "Projectile.h"
#include <memory>
#include <iostream>

enum class Direction {Right, Left};
enum class Level {One, Two, Three};

class Renderer;
class Invader {
public:
    Invader(const std::shared_ptr<Renderer>& renderer, float width, float height, float xCoord, float yCoord, Level level);
    void Draw();
    void Move(int step);
    void MoveY(int step);
    void Shoot();
    void Kill();
    void Revive();

    Point2D GetPoint() const noexcept { return m_rect.GetPoint(); }
    const Rectangle& GetRectangle() const;
    Rectangle& GetRectangle();

    std::shared_ptr<Projectile> GetProjectile() const noexcept { return m_projectile; }
    bool GetProjectileIsLaunched() const noexcept { return projectileIsLaunched; }

    void SetDirection(Direction direction);
    Direction GetDirection() const noexcept { return m_direction; }

    void ToggleDirection();

    void SetLevel(Level level) noexcept;
    Level GetLevel() const noexcept;

    bool IsDead() const noexcept { return m_isDead; }
    void ResetProjectile();
private:
    Direction m_direction = Direction::Right;
    Rectangle m_rect;
    std::shared_ptr<Projectile> m_projectile;
   
    bool m_isDead = false;
    bool projectileIsLaunched = false;
    Level m_alienLevel;
};