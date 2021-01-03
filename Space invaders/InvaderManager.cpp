#include "InvaderManager.h"
#include "Invader.h"
#include <thread>
#include <chrono>

InvaderManager::InvaderManager(const std::shared_ptr<Renderer>& renderer, float width, float height) 
    :
    m_width(width),
    m_height(height)
{
    std::vector<std::shared_ptr<Invader>> invaderRowVector;

    for (int i = 0, k = 0; i < 5; i++) {
        for (size_t j = 0, l = 0; j < 11; j++) {

            invaderRowVector.push_back(std::make_shared<Invader>(renderer, width, height, l, k));
            l += 50;
        }
        m_invaders.emplace_back(std::move(invaderRowVector));
        k += 50;
    }
   
}

void InvaderManager::Move() {
    using namespace std::chrono_literals;

    bool isDirectionToggled = false;

    for (const auto invaderRow : m_invaders) {
        if (!invaderRow.empty()) {
            if (invaderRow.back()->GetPoint().x == 800 - m_width) {
                isDirectionToggled = true;
            }

            else if (invaderRow.front()->GetPoint().x == 0) {
                isDirectionToggled = true;
            }

            for (auto invader : invaderRow) {
                if (isDirectionToggled) {
                    invader->ToggleDirection();
                    invader->MoveY();
                }
                invader->Move();
                invader->Shoot();
            }
        }
    }
}

void InvaderManager::Show() {
    for (const auto invaderRow : m_invaders) {
        for (const auto invader : invaderRow) {
            invader->Draw();
        }
    }
}

const  std::vector<std::vector<std::shared_ptr<Invader>>>& InvaderManager::GetInvaders() {
    return m_invaders;
}

void InvaderManager::KillInvaderAtPosition(int xPos, int yPos) {
    if (!m_invaders.empty()) {
        auto& invaderRow = m_invaders.at(yPos);

        if (!invaderRow.empty()) {
            invaderRow.erase(invaderRow.begin() + xPos);
        }
    }  
}

