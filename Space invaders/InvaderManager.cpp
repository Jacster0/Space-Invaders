#include "InvaderManager.h"
#include "Invader.h"
#include "Defender.h"
#include <thread>
#include <chrono>
#include <random>
#include <algorithm>
#include <iterator>
#include <cassert>

InvaderManager::InvaderManager(const std::shared_ptr<Renderer>& renderer, float width, float height) 
    :
    m_width(width),
    m_height(height)
{
    InvaderList invaderRowVector;

    for (int i = 0, k = 50; i < 5; i++) {
        for (size_t j = 0, l = 50; j < 11; j++) {

            invaderRowVector.push_back(std::make_shared<Invader>(renderer, width, height, l, k));
            l += 50;
        }
        m_invaders.emplace_back(std::move(invaderRowVector));
        k += 50;
    }
   //Add the last row to the freeInvaders list
    const auto& lastRow = m_invaders.at(m_invaders.size() - 1);
    std::copy(lastRow.begin(), lastRow.end(), std::back_inserter(freeInvaders));
}

void InvaderManager::Move(float speedFactor) {
    using namespace std::chrono_literals;

    auto timePoint = std::chrono::steady_clock::now;
    bool isDirectionToggled = false;

    auto dt = std::chrono::steady_clock::now() - m_timePoint;

    for (const auto invaderRow : m_invaders) {
        for (auto invader : invaderRow) {
            if (invader->GetProjectileIsLaunched()) {
                invader->GetProjectile()->Move(-1 * speedFactor);
            }
        }
    }

    if (std::chrono::duration_cast<std::chrono::milliseconds>(dt) < 500ms) {
        return;
    }

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

            for (auto invader : invaderRow) {
                if (isDirectionToggled) {
                    invader->ToggleDirection();
                    invader->MoveY();
                }
                invader->Move();
            }
        }
    }
    m_timePoint = std::chrono::high_resolution_clock::now();
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
                invader->Draw();

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
    int score = 30;

    auto& invader = m_invaders.at(yPos).at(xPos);
    //kill the invader
    invader->Kill();
    //decrement the number of alive invaders
    m_numberOfInvadersAlive--;

    bool isFreeInvader = (std::find(freeInvaders.begin(), freeInvaders.end(), invader) != freeInvaders.end());

    //Non-free invaders are harder to hit so we double the score
    if (!isFreeInvader) {
        score = 60;
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
        else if (projectileRectangle.GetPoint().y + projectileRectangle.GetHeight() >= 600) {
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
