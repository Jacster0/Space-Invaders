#pragma once
#include "Rectangle.h"
#include "Projectile.h"
#include <memory>

enum class Direction {Right, Left};

class m_projectile;
class Renderer;
class Invader {
public:
    Invader(const std::shared_ptr<Renderer>& renderer, float width, float height, float xCoord, float yCoord);

    void Die();
    void Draw();
    void Move();
    void MoveY();
    void Shoot();

    Point2D GetPoint() const noexcept { return m_rect.GetPoint(); }
    Rectangle GetRectangle();

    void SetDirection(Direction direction);
    Direction GetDirection() const noexcept { return m_direction; }

    void ToggleDirection();

    bool IsDead() const noexcept { return m_isDead; }
private:
    Direction m_direction = Direction::Right;
    Rectangle m_rect;
    std::unique_ptr<Projectile> m_projectile;
    int speed = 2;
    int speedY = 10;

    bool m_isDead{};
    bool projectileIsLaunched = false;
};