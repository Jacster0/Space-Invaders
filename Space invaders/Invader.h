#pragma once
#include "Rectangle.h"
#include <memory>

enum class Direction {Right, Left};
class Renderer;
class Invader {
public:
    Invader(const std::shared_ptr<Renderer>& renderer);

    void Die();
    void Draw();
    void Move();
    void Shoot();

    void SetDirection(Direction direction);
private:
    void ToggleDirection();

    bool m_isDead{};
    Direction m_direction = Direction::Right;
    Rectangle m_rect;
    int speed = 2;
};