#include "Game.h"
#include "SDL.h"
#include "Renderer.h"
#include "Window.h"
#include "BackGroundManager.h"

Game::Game()  {
    SDL_Init(SDL_INIT_EVERYTHING);

    Window* wnd = Window::Create();
    wnd->Show();

    m_renderer = std::make_shared<Renderer>(*wnd,0, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    m_renderer->SetColor(0, 0, 0, 255);
    m_renderer->Clear();

    m_defender = std::make_shared<Defender>(m_renderer);
    m_invManger = InvaderManager(m_renderer, 26, 26);

    m_backgroundManager = std::make_unique<BackGroundScreenManager>(m_renderer, m_numberOfLives);

    m_lastTime = SDL_GetTicks();
}

Game::~Game() {
    Window::Destroy();
    SDL_Quit();
}

int Game::Run() {
    while (true) {
        if (m_playerWon) {
            //Restart the game, keep track of the score
            Restart(true);
        }

        else if (m_gameOver) {
            //display the game over scene
            m_returnCode = m_backgroundManager->ShowGameOverDisplay();

            //If the returnCode is SDL_QUIT, exit immediately
            if (m_returnCode == ReturnCode::Quit) {
                return static_cast<int>(m_returnCode);
            }
            else if (m_returnCode == ReturnCode::PlayAgain) {
                //Restart the game, reset the score
                Restart(false);
            }
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

//Updates the Game state, called once every frame
void Game::Update() {
    //Update the Background Manager
    m_backgroundManager->Update(m_score);

    //if there is no invaders left, the Defender (player) won the game
    if (m_invManger.GetNumberOfAliveInvaders() == 0) {
        m_playerWon = true;
        return;
    }
    //If the defender is out of lives, mark the game as gameover.
    else if (m_numberOfLives == 0) {
        m_gameOver = true;
        return;
    }

    m_currentTime = SDL_GetTicks();
    m_speedFactor = m_currentTime - m_lastTime;

    ProcessInput();

    if (m_defender->GetProjectileIsLaunched()) {
        m_defender->GetProjectile()->Move(m_speedFactor);
    }

    m_invManger.Shoot();
    m_invManger.Move(m_speedFactor);

    CheckCollision();

    m_backgroundManager->ClearScreen();

    m_lastTime = m_currentTime;
}

void Game::Render() {
    m_defender->Draw();
    if (m_defender->GetProjectileIsLaunched()) {
        m_defender->GetProjectile()->Draw();
    }
    m_invManger.Show();
    m_backgroundManager->Show();
    m_renderer->Present();
}

void Game::Restart(bool keepScore) {
    m_defender->Reset();
    m_invManger.Reset();
    m_backgroundManager->Reset();

    //Everything that needs to be reset in the Game class
    m_numberOfLives = 3;
    m_score = (keepScore) ? m_score : 0;
    m_returnCode = 0;
    m_gameOver = false;
    m_playerWon = false;
}

void Game::CheckCollision() {
    //invader collisions
    m_invManger.CheckCollision(m_defender);

    if (m_defender->IsHit()) {
        m_numberOfLives--;
        //Tell the backroundManager that the Defender was hit
        m_backgroundManager->DefenderHit();
        //Reset the defender so it can be hit again 
        m_defender->ResetHit();
    }

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
                        m_score += m_invManger.KillInvaderAtPosition(xPos, yPos);
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
