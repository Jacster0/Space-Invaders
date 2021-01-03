#pragma once
#include <vector>
#include <memory>
#include "Point2D.h"

class Invader;
class Renderer;
class InvaderManager {
public:
    InvaderManager() = default;
    InvaderManager(const std::shared_ptr<Renderer>& renderer, float width, float height);

    void Move();
    void Show();
    const std::vector<std::vector<std::shared_ptr<Invader>>>& GetInvaders();
    void KillInvaderAtPosition(int xPos, int yPos);
private:
    std::vector<std::vector<std::shared_ptr<Invader>>> m_invaders{};
    float m_width{0};
    float m_height{0};
};