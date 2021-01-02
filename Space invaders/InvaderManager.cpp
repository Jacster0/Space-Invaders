#include "InvaderManager.h"
#include "Invader.h"

InvaderManager::InvaderManager(const std::shared_ptr<Renderer>& renderer, float width, float height) 
    :
    m_width(width),
    m_height(height)
{
    for (size_t i = 0, j = 0; i < 4; i++) {
        
        m_invaders.push_back(std::make_shared<Invader>(renderer, width, height, 100 + j, 50));

        j += 100;
    }
}

void InvaderManager::Move() {
    bool isDirectionToggled = false;
    if (!m_invaders.empty()) {
        if (m_invaders.back()->GetPoint().x == 800 - m_width) {
            isDirectionToggled = true;
        }

        else if (m_invaders.front()->GetPoint().x == 0) {
            isDirectionToggled = true;
        }

        for (auto invader : m_invaders) {
            if (isDirectionToggled) {
                invader->ToggleDirection();
                invader->MoveY();
            }
            invader->Move();
            invader->Shoot();
        }
    }
}

void InvaderManager::Show() {
    for (auto invader : m_invaders) {
        invader->Draw();
    }
}

Point2D InvaderManager::GetLowestRowCoords() {
    return m_invaders.at(0)->GetPoint();
}

const std::vector<std::shared_ptr<Invader>>& InvaderManager::GetInvaders() {
    return m_invaders;
}

void InvaderManager::KillInvaderAtPosition(int pos) {
    if (!m_invaders.empty()) {
        m_invaders.erase(m_invaders.begin() + pos);
    }  
}
