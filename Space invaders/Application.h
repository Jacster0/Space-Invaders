#pragma once
#include <optional>
#include <memory>
#include "Defender.h"
#include "SDL.h"
#include "Invader.h"
#include "Projectile.h"
#include <chrono>

class Renderer;
class Application {
public:
    Application();
    ~Application();
    int Run();
    void ProcessInput();
    void Update();
    void Render();
private:
    void HandleKeyStrokes();
    SDL_Event m_event;
    std::shared_ptr<Renderer> m_renderer;

    std::unique_ptr<Defender> m_defender;
    std::unique_ptr<Invader>  m_invader;

    static constexpr float speed = 4;
};