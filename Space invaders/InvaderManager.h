#pragma once
#include <vector>
#include <memory>

class Invader;
class Renderer;
class InvaderManager {
public:
    InvaderManager() = default;
    InvaderManager(const std::shared_ptr<Renderer>& renderer, float width, float height);

    void Move();
    void Show();
private:
    std::vector<std::shared_ptr<Invader>> m_invaders;
    float m_width;
    float m_height;
};