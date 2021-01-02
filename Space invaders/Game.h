#pragma once
#include <optional>
#include <memory>
#include "Defender.h"
#include "SDL.h"
#include "Invader.h"
#include "Projectile.h"
#include "InvaderManager.h"
#include "CollisionDetection.h"

class Renderer;
class Game {
public:
    Game();
    ~Game();
    int Run();
    void ProcessInput();
    void Update();
    void Render();
private:
    void CheckCollision();
    void HandleKeyStrokes();
    SDL_Event m_event;
    std::shared_ptr<Renderer> m_renderer;

    std::unique_ptr<Defender> m_defender;

    InvaderManager m_invManger;
    CollisionDetection m_collisonDetection;

    static constexpr float speed = 4;
    bool canShoot = true;
};