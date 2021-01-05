#include "Game.h"
#include "SDL.h"
#include "Renderer.h"
#include "Window.h"

Game::Game()  {
    SDL_Init(SDL_INIT_EVERYTHING);

    Window* wnd = Window::Create();
    wnd->Show();

    m_renderer = std::make_shared<Renderer>(*wnd,0, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    m_renderer->SetColor(0, 0, 0, 255);
    m_renderer->Clear();

    m_defender = std::make_shared<Defender>(m_renderer);

    m_invManger = InvaderManager(m_renderer, 25, 25);

    m_lastTime = SDL_GetTicks();
}

Game::~Game() {
    Window::Destroy();
    SDL_Quit();
}

int Game::Run() {
    while (true) {
        //If the returnCode is SDL_QUIT, exit immediately
        if (m_returnCode == SDL_QUIT) {
            return static_cast<int>(m_returnCode);
        }
        HandleEvents();
        Update();
        Render();
    }
    return m_returnCode;
}

void Game::ProcessInput() {
    HandleKeyStrokes();
}

void Game::Update() {
    m_currentTime = SDL_GetTicks();

    m_speedFactor = m_currentTime - m_lastTime;

    ProcessInput();

    if (m_defender->GetProjectileIsLaunched()) {
        m_defender->GetProjectile()->Move(m_speedFactor);
    }

    m_invManger.Shoot();
    m_invManger.Move(m_speedFactor);

    CheckCollision();

    m_renderer->SetColor(0, 0, 0,255);
    m_renderer->Clear();

    m_lastTime = m_currentTime;
}

void Game::Render() {
    m_defender->Draw();
    if (m_defender->GetProjectileIsLaunched()) {
        m_defender->GetProjectile()->Draw();
    }
    m_invManger.Show();
    m_renderer->Present();
}

void Game::CheckCollision() {
    //invader collisions
    m_invManger.CheckCollision(m_defender);

    //Defender collision
    auto projectile = m_defender->GetProjectile();

    auto projectileRectangle = projectile->GetRectangle();

    //If the defender have not launched the projectile there is no collision detection to do for the defender
    if (!m_defender->GetProjectileIsLaunched()) {
        canShoot = true;
        return;
    }
    //If the projectile have missed all the invaders and hit the upper bound, reset the projectile so we
    //can shoot again
    if (projectileRectangle.GetPoint().y <= 0) {
        m_defender->ResetProjectile();
        canShoot = true;
    }
    else {
        const auto invaders = m_invManger.GetInvaders();

        int xPos = 0;
        int yPos = 0;
        for (const auto& invaderRow : invaders) {
            xPos = 0;
            for (const auto& invader : invaderRow) {
                //Don't do any collision detection on a dead invader
                if (!invader->IsDead()) {
                    if (m_collisonDetection.CheckCollison(projectileRectangle, invader->GetRectangle())) {
                        //Kill the invader that got hit
                        m_invManger.KillInvaderAtPosition(xPos, yPos);
                        //reset the projectile so that we can shoot again
                        m_defender->ResetProjectile();
                        canShoot = true;

                        return;
                    }
                }
                xPos++;
            }
            yPos++;
        }
    }
}

void Game::HandleKeyStrokes() {
    const Uint8* state = SDL_GetKeyboardState(nullptr);

    if (state[SDL_SCANCODE_ESCAPE]) {
        m_returnCode = SDL_QUIT;
    }

    if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]) {
        m_defender->Move(speed * static_cast<float>(m_speedFactor));
    }

    if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]) {
        m_defender->Move(-speed * static_cast<float>(m_speedFactor));
    }
    
    if (canShoot) {
        if (state[SDL_SCANCODE_SPACE]) {
            m_defender->Shoot();
            canShoot = false;
        }
    }
}

void Game::HandleEvents() {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_QUIT) {
            m_returnCode = SDL_QUIT;
        }
    }
}
