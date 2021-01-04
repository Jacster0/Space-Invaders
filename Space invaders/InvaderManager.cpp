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
            //If the invader is dead but it has an inflight projectile, draw and move the projectile
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

void InvaderManager::KillInvaderAtPosition(int xPos, int yPos) {
        auto& invader = m_invaders.at(yPos).at(xPos);
        //kill the invader
        invader->Kill();

        //Add the invader just above the killed invader in the freeInvader list
        auto abovePos = yPos - 1;
        auto belowPos = yPos + 1;

        if (abovePos >= 0) {
            auto& invaderAbove = m_invaders.at(abovePos).at(xPos);
            freeInvaders.push_back(invaderAbove);
        }
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

        if (m_collisionDetection.CheckCollison(projectileRectangle, defender->GetRectangle())) {
            //reset the projectile so that the invaders can shoot again
            m_dirtyInvader->ResetProjectile();
            m_canShoot = true;
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
