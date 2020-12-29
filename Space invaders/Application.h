#pragma once
#include <optional>
#include <memory>
#include "Defender.h"
#include "SDL.h"
#include "Projectile.h"

class Renderer;
class Application {
public:
    Application();
    ~Application();
    std::optional<int> Run();
    std::optional<int> ProcessInput();
    void Update();
    void Render();
private:
    void HandleKeyStrokes();
    SDL_Event m_event;
    std::shared_ptr<Renderer> m_renderer;
    std::unique_ptr<Defender> m_defender;

    static constexpr int speedFactor = 15;
};