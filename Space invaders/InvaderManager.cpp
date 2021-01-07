#include "InvaderManager.h"
#include "Invader.h"
#include "Defender.h"
#include <chrono>
#include <random>
#include <algorithm>
#include <iterator>
#include <cassert>
#include "SDL.h"
#include "SDL_image.h"
#include "Renderer.h"

using namespace std::chrono_literals;

InvaderManager::InvaderManager(const std::shared_ptr<Renderer>& renderer, float width, float height) 
    :
    m_renderer(renderer),
    m_width(width),
    m_height(height)
{
    //set the initial limit value to 500 seconds
    m_limit = 500ms;

    InvaderList invaderRowVector;
    //Load some textures
    m_alienLevel1Textures = {
        IMG_LoadTexture(m_renderer->GetSDLRenderer(), R"(Resources\AlienLevel1First.png)"),
        IMG_LoadTexture(m_renderer->GetSDLRenderer(), R"(Resources\AlienLevel1Second.png)")
    };

    m_alienLevel2Textures = {
        IMG_LoadTexture(m_renderer->GetSDLRenderer(), R"(Resources\AlienLevel2First.png)"),
        IMG_LoadTexture(m_renderer->GetSDLRenderer(), R"(Resources\AlienLevel2Second.png)")
    };

    m_alienLevel3Textures = {
        IMG_LoadTexture(m_renderer->GetSDLRenderer(), R"(Resources\AlienLevel3First.png)"),
        IMG_LoadTexture(m_renderer->GetSDLRenderer(), R"(Resources\AlienLevel3Second.png)")
    };

    m_alienLevel1textureToRender = m_alienLevel1Textures[0];
    m_alienLevel2textureToRender = m_alienLevel2Textures[0];
    m_alienLevel3textureToRender = m_alienLevel3Textures[0];
    
    Level alienLevel = Level::Three;

    for (int i = 0, yPos = 50; i < 5; i++) {
        for (size_t j = 0, xPos = 50; j < 11; j++) {

            if (i < 1) {
                alienLevel = Level::Three;
            }
            else if (i < 3) {
                alienLevel = Level::Two;
            }
            else {
                alienLevel = Level::One;
            }
            invaderRowVector.push_back(std::make_shared<Invader>(renderer, width, height, xPos, yPos, alienLevel));
            xPos += 50;
        }

        m_invaders.emplace_back(std::move(invaderRowVector));
        yPos += 50;
    }
   //Add the last row to the freeInvaders list
    const auto& lastRow = m_invaders.at(m_invaders.size() - 1);
    std::copy(lastRow.begin(), lastRow.end(), std::back_inserter(freeInvaders));
}

InvaderManager::~InvaderManager() {
    for (auto texture : m_alienLevel1Textures) {
        SDL_DestroyTexture(texture);
    }
    for (auto texture : m_alienLevel2Textures) {
        SDL_DestroyTexture(texture);
    }
    for (auto texture : m_alienLevel3Textures) {
        SDL_DestroyTexture(texture);
    }
}

std::optional<int> InvaderManager::Move(float speedFactor) {
    auto timePoint = std::chrono::steady_clock::now;
    bool isDirectionToggled = false;

    auto dt = std::chrono::steady_clock::now() - m_timePoint;

    if (m_numberOfInvadersAlive <= 37) {
        m_limit = 250ms;
    }

    if (m_numberOfInvadersAlive <= 27) {
        m_limit = 150ms;
    }

    if (m_numberOfInvadersAlive == 1) {
        m_limit = 20ms;
        //If there is only one aline left, reduce the step in Y led to make it a little bit
        //easier for the player.
        m_stepY = 25;
    }

    for (const auto invaderRow : m_invaders) {
        for (auto invader : invaderRow) {
            if (invader->GetProjectileIsLaunched()) {
                invader->GetProjectile()->Move(-speedFactor);
            }
        }
    }

    if (std::chrono::duration_cast<std::chrono::milliseconds>(dt) < m_limit) {
        //Just return an empty optional
        return {};
    }

    //Decide which alien to render this move
    const auto index = (++counter % 2 == 0) ? 0 : 1;

    m_alienLevel1textureToRender = m_alienLevel1Textures[index];
    m_alienLevel2textureToRender = m_alienLevel2Textures[index];
    m_alienLevel3textureToRender = m_alienLevel3Textures[index];
   
    //Do the move logic
    for (const auto invaderRow : m_invaders) {
        if (!invaderRow.empty()) {
            for (auto invader : invaderRow) {
                if (invader->IsDead()) {
                    continue;
                }
                if (invader->GetPoint().x == 800 - m_width) {
                    isDirectionToggled = true;
                }
                else if (invader->GetPoint().x == 0) {
                    isDirectionToggled = true;
                }
            }
        }
    }

    for (const auto invaderRow : m_invaders) {
        for (auto invader : invaderRow) {
            if (invader->IsDead()) {
                continue;
            }
            if (isDirectionToggled) {
                invader->ToggleDirection();
                invader->MoveY(m_stepY);

                if (invader->GetPoint().y + invader->GetRectangle().GetHeight() >= m_groundLevel) {
                    //an invader has hit the ground and succesfully invaded the planet
                    //just return an arbitrary value to indicate that this even has occure.
                    return 1;
                }
            }
            invader->Move(m_stepX);
        }
    }
    m_timePoint = std::chrono::high_resolution_clock::now();

    return {};
}

void InvaderManager::Show() {
    for (const auto& invaderRow : m_invaders) {
        for (const auto& invader : invaderRow) {
            //If the invader is dead but it has an inflight projectile, draw the projectile
            if (invader->IsDead()) {
                if (invader->GetProjectileIsLaunched()) {
                    auto projectile = invader->GetProjectile();
                    projectile->Draw();
                }
            }

            else {
                //Render a image to the invader rectangle
                SDL_Rect rect{ invader->GetRectangle().GetPoint().x, invader->GetRectangle().GetPoint().y ,m_width ,m_height };

                switch (invader->GetLevel())
                {
                case Level::One:
                    SDL_RenderCopy(m_renderer->GetSDLRenderer(), m_alienLevel1textureToRender, nullptr, &rect);
                        break;
                case Level::Two:
                    SDL_RenderCopy(m_renderer->GetSDLRenderer(), m_alienLevel2textureToRender, nullptr, &rect);
                    break;
                case Level::Three:
                    SDL_RenderCopy(m_renderer->GetSDLRenderer(), m_alienLevel3textureToRender, nullptr, &rect);
                    break;
                }
               
                if (invader->GetProjectileIsLaunched()) {
                    auto projectile = invader->GetProjectile();
                    projectile->Draw();
                }
            }
        }
    }
}

const std::vector<std::vector<std::shared_ptr<Invader>>>& InvaderManager::GetInvaders() {
    return m_invaders;
}

int InvaderManager::KillInvaderAtPosition(int xPos, int yPos) {
    int score{};

    auto& invader = m_invaders.at(yPos).at(xPos);
    //kill the invader
    invader->Kill();
    //decrement the number of alive invaders
    m_numberOfInvadersAlive--;

    switch (invader->GetLevel()) {
    case Level::One:
        score = 10;
        break;
    case Level::Two:
        score = 20;
        break;
    case Level::Three:
        score = 30;
        break;
    }

    bool isFreeInvader = (std::find(freeInvaders.begin(), freeInvaders.end(), invader) != freeInvaders.end());

    //Non-free invaders are harder to hit so we double the score
    if (!isFreeInvader) {
        score *= 2;
    }

    if (yPos < m_invaders.size() - 1) {
        //If the dead invader was not a free invader, we cannot make the invader above a free invader,
        //because the invader below the dead invader is still alive and blocking.
        if (!isFreeInvader) {
            return score;
        }
    }

    //find the invader above the dead invader and make him free
    auto abovePos = yPos - 1;
    if (abovePos >= 0) {
        auto& invaderAbove = m_invaders.at(abovePos).at(xPos);
        freeInvaders.push_back(invaderAbove);
    }

    return score;
}

void InvaderManager::Shoot() {
    if (m_canShoot) {
        //Remove any dead invader in the freeInvaders list (dead invaders cannot shoot)
        freeInvaders.erase(
            std::remove_if(freeInvaders.begin(), freeInvaders.end(),
                [](const std::shared_ptr<Invader>& invader) {
                    return invader->IsDead();
                }),
            freeInvaders.end());

        if (freeInvaders.empty()) {
            return;
        }
        //Set up the random generating stuff
        std::random_device device;
        std::default_random_engine rng(device());
        std::uniform_int_distribution<int> dist(0, freeInvaders.size() - 1);

        //Make the actual invader shoot
        auto& invader = freeInvaders.at(dist(rng));
        invader->Shoot();
        
        m_canShoot = false;
        //retrieve the actual invader that made the shot 
        m_dirtyInvader = invader;
    }
}

void InvaderManager::CheckCollision(const std::shared_ptr<Defender>& defender) {
    if (m_dirtyInvader) {
        auto projectileRectangle = m_dirtyInvader->GetProjectile()->GetRectangle();

        //Check for collisions of the invader projectile and the defender body
        if (m_collisionDetection.CheckCollison(projectileRectangle, defender->GetRectangle())) {
            //mark the defender as hit, removing one life from the defender
            defender->Hit();
            //reset the projectile so that the invaders can shoot again
            m_dirtyInvader->ResetProjectile();
            m_canShoot = true;
        }

        //Check for collisions of the invader projectile and the defender projectile
        else if (m_collisionDetection.CheckCollison(projectileRectangle, defender->GetProjectile()->GetRectangle())) {
            //reset the projectile so that the invaders can shoot again
            m_dirtyInvader->ResetProjectile();
            m_canShoot = true;

            //We need to reset the defenders projectile if a collision has occured
            defender->ResetProjectile();
        }

        //if the projectile missed the defender and all the barriers, reset the projectile so that 
        //the invaders can shoot again
        else if (projectileRectangle.GetPoint().y + projectileRectangle.GetHeight() >= m_groundLevel) {
            m_dirtyInvader->ResetProjectile();
            m_canShoot = true;
            return;
        }
    }
}

//Resets the InavderManager and all the Invaders that is managed by this manager
void InvaderManager::Reset() {
    //Make all invaders live again
    m_numberOfInvadersAlive = 5 * 11;
    m_limit = 500ms;
    
    InvaderList invaderRowVector;
    float yPos = 50.0f;
    float xPos = 50.0f;

    //reset the invaders position
    for (int i = 0, yPos = 50; i < 5; i++) {
        invaderRowVector = std::move(m_invaders.at(i));
        for (size_t j = 0, xPos = 50; j < 11; j++) {
            auto& invader = invaderRowVector.at(j);

            //Reset the direction
            invader->SetDirection(Direction::Right);
            //Revive the invader
            invader->Revive();
            //reset the invaders positions
            invader->GetRectangle().SetPoint({static_cast<float>(xPos), static_cast<float>(yPos)});
            //reset the invaders projectile
            invader->ResetProjectile();
            //Advance the x position
            xPos += 50;
        }
        m_invaders.at(i) = std::move(invaderRowVector);

        // advance the y position
        yPos += 50;
    }

    //clear the freeInvaders list
    freeInvaders.clear();

    //Add the last row to the freeInvaders list
    const auto& lastRow = m_invaders.at(m_invaders.size() - 1);
    std::copy(lastRow.begin(), lastRow.end(), std::back_inserter(freeInvaders));

    //enable shooting
    m_canShoot = true;
}

int InvaderManager::GetNumberOfAliveInvaders() const noexcept {
    return m_numberOfInvadersAlive;
}
