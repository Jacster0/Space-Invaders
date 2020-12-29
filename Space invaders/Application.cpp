#include "Application.h"
#include "SDL.h"
#include "Renderer.h"
#include "Window.h"

Application::Application()  {
    SDL_Init(SDL_INIT_EVERYTHING);

    Window* wnd = Window::Create();
    wnd->Show();

    m_renderer = std::make_shared<Renderer>(*wnd);
    m_renderer->SetColor(0, 255, 0, 255);
    m_renderer->Clear();

    m_defender = std::make_unique<Defender>(m_renderer);
}

Application::~Application() {
    Window::Destroy();
    SDL_Quit();
}

std::optional<int> Application::Run() {
    while (true) {
        SDL_WaitEvent(&m_event);

        if (ProcessInput()) {
            break;
        }

        Update();
        Render();
    }
    return {};
}

std::optional<int> Application::ProcessInput() {
    HandleKeyStrokes();

    return {};
}

void Application::Update() {
    m_renderer->SetColor(0, 255, 0,255);
    m_renderer->Clear();
}

void Application::Render() {
    m_defender->Draw();
    m_renderer->Present();
}

void Application::HandleKeyStrokes() {
    switch (m_event.type) {
    case SDL_KEYDOWN:
        switch (m_event.key.keysym.sym) {
        case SDLK_RIGHT:
            m_defender->Move(speedFactor);
            break;
        case SDLK_LEFT:
            m_defender->Move(-speedFactor);
            break;
        }
    }
}
