#pragma once
#include <optional>
#include <memory>
#include "Defender.h"
#include "SDL.h"
#include "Invader.h"
#include "Projectile.h"
#include "InvaderManager.h"
#include "CollisionDetection.h"

class BackGroundScreenManager;
class Renderer;
class Game {
public:
    Game();
    ~Game();
    int Run();
    void ProcessInput();
    void Update();
    void Render();
    void Restart(bool keepScore);
    void DrawGround();
private:
    void CheckCollision();
    void HandleKeyStrokes();
    void HandleEvents();
    SDL_Event m_event;

    std::shared_ptr<Renderer> m_renderer;
    std::shared_ptr<Defender> m_defender;

    std::unique_ptr<InvaderManager> m_invManger;
    CollisionDetection m_collisonDetection;
    std::unique_ptr<BackGroundScreenManager> m_backgroundManager;

    Uint32 m_returnCode = 0;

    Uint32 m_currentTime = 0;
    Uint32 m_lastTime = 0;
    Uint32 m_speedFactor = 0;

    static constexpr float step = 0.5f;
    bool canShoot = true;

    int m_numberOfLives = 3;
    bool m_gameOver = false;
    bool m_playerWon = false;

    int m_score{0};
};