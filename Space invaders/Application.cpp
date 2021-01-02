#include "Application.h"
#include "SDL.h"
#include "Renderer.h"
#include "Window.h"

Application::Application()  {
    SDL_Init(SDL_INIT_EVERYTHING);

    Window* wnd = Window::Create();
    wnd->Show();

    m_renderer = std::make_shared<Renderer>(*wnd,0, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    m_renderer->SetColor(0, 0, 0, 255);
    m_renderer->Clear();

    m_defender = std::make_unique<Defender>(m_renderer);

    m_invManger = InvaderManager(m_renderer, 25, 25);
}

Application::~Application() {
    Window::Destroy();
    SDL_Quit();
}

int Application::Run() {
    while (true) {
        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) {
            if (sdlEvent.type == SDL_QUIT) {
                return static_cast<int>(SDL_QUIT);
            }
        }
        
        Update();
        Render();
    }
    return 0;
}
void Application::ProcessInput() {
    HandleKeyStrokes();
}

void Application::Update() {
    CheckCollision();
    ProcessInput();

    m_invManger.Move();

    m_renderer->SetColor(0, 0, 0,255);
    m_renderer->Clear();
}

void Application::Render() {
    m_defender->Draw();
    m_invManger.Show();
    m_renderer->Present();
}

void Application::CheckCollision() {
    auto projectile = m_defender->GetProjectile();

    auto projectileRectangle = projectile->GetRectangle();

    if (projectileRectangle.GetPoint().y == 0) {
        m_defender->ResetProjectile();
        canShoot = true;
    }
    else {
        const auto invaders = m_invManger.GetInvaders();

        int pos = 0;
        for (const auto invader : invaders) {
            if (m_collisonDetection.CheckCollison(projectile->GetRectangle(), invader->GetRectangle())) {
                //Kill the invader that got hit
                m_invManger.KillInvaderAtPosition(pos);
                //reset the projectile so that we can shoot again
                m_defender->ResetProjectile();
                canShoot = true;

                return;
            }
            pos++;
        }
    }
}

void Application::HandleKeyStrokes() {
    const Uint8* state = SDL_GetKeyboardState(nullptr);

    if (state[SDL_SCANCODE_RIGHT]) {
        m_defender->Move(static_cast<int>(speed));
    }

    if (state[SDL_SCANCODE_LEFT]) {
        m_defender->Move(static_cast<int>(-speed));
    }
    
    if (canShoot) {
        if (state[SDL_SCANCODE_SPACE]) {
            m_defender->Shoot();
            canShoot = false;
        }
    }
}
