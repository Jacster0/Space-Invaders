#pragma once
#include <vector>
#include <memory>
#include "Point2D.h"
#include "CollisionDetection.h"

class Defender;
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
    void Shoot();
    void CheckCollision(const std::shared_ptr<Defender>& defender);
private:
    using InvaderList = std::vector<std::shared_ptr<Invader>>;

    std::vector<InvaderList> m_invaders;
    //Any invader in the free Invaders list can freely shoot projectiles without getting blocked by other invaders
    InvaderList freeInvaders;
    //pointer to an invader that just shot their projectile
    std::shared_ptr<Invader> m_dirtyInvader{ nullptr };

    CollisionDetection m_collisionDetection;

    float m_width{0};
    float m_height{0};
    bool m_canShoot{ true };
};