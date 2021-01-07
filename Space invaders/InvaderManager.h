#pragma once
#include <vector>
#include <memory>
#include <chrono>
#include <array>
#include <optional>
#include "Point2D.h"
#include "CollisionDetection.h"

class Defender;
class Invader;
class Renderer;
class SDL_Texture;
class InvaderManager {
public:
    InvaderManager() = default;
    InvaderManager(const std::shared_ptr<Renderer>& renderer, float width, float height);
    ~InvaderManager();

    std::optional<int> Move(float speedFactor);
    void Show();
    const std::vector<std::vector<std::shared_ptr<Invader>>>& GetInvaders();
    int KillInvaderAtPosition(int xPos, int yPos);
    void Shoot();
    void CheckCollision(const std::shared_ptr<Defender>& defender);
    void Reset();

    int GetNumberOfAliveInvaders() const noexcept;
private:
    using InvaderList = std::vector<std::shared_ptr<Invader>>;

    std::vector<InvaderList> m_invaders;
    //Any invader in the free Invaders list can freely shoot projectiles without getting blocked by other invaders
    InvaderList freeInvaders;
    //pointer to an invader that just shot their projectile
    std::shared_ptr<Invader> m_dirtyInvader{ nullptr };

    CollisionDetection m_collisionDetection;
    std::chrono::steady_clock::time_point m_timePoint = std::chrono::steady_clock::now();

    float m_width{0};
    float m_height{0};
    bool m_canShoot{ true };

    //There are 5 rows of invaders, and every row contains 11 invaders
    int m_numberOfInvadersAlive = 5 * 11;

    std::array<SDL_Texture*, 2> m_alienLevel1Textures;
    std::array<SDL_Texture*, 2> m_alienLevel2Textures;
    std::array<SDL_Texture*, 2> m_alienLevel3Textures;
   
    SDL_Texture* m_alienLevel1textureToRender = nullptr;
    SDL_Texture* m_alienLevel2textureToRender = nullptr;
    SDL_Texture* m_alienLevel3textureToRender = nullptr;

    std::shared_ptr<Renderer> m_renderer;

    unsigned long counter = 0;
    std::chrono::milliseconds m_limit;
    
    //The defenders upper left corner is at y location 550, and the defenderts height is 32 pixels
    //So the groundLevel which the aliens are aiming for will be at location 550 + 32 = 582
    static constexpr int m_groundLevel = 550 + 32;

    static constexpr int m_stepX = 10;
    int m_stepY = 50;
};