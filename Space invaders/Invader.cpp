#include "Invader.h"
#include "Renderer.h"

#include <algorithm>

Invader::Invader(const std::shared_ptr<Renderer>& renderer)
    :
    m_rect({30,30}, 255,255,255,255, 25,25, renderer)
{
}

void Invader::Die() {
    m_isDead = true;
}

void Invader::Draw() {
    if (!m_isDead) {
        m_rect.render(RenderFlag::Fill);
    }
}

void Invader::Move() {
    int oldX = m_rect.GetPoint().x;
    float screenCoordMax = 800.0f - m_rect.GetWidth();
    Point2D newLoc = m_rect.GetPoint();

    if (m_direction == Direction::Right) {
        newLoc.x += speed;
    }
    else {
        newLoc.x -= speed;
    }
   
    //clamp the x position inside our screen coords
    newLoc.x = std::clamp(newLoc.x, 0.0f, 800.0f - screenCoordMax);
    m_rect.SetPoint(newLoc);

    //Change direction of the Invader if it has hit any of the screens border
    if (newLoc.x == 800 - m_rect.GetWidth() || newLoc.x == 0) {
        ToggleDirection();
    }
}

void Invader::SetDirection(Direction direction) {
    m_direction = direction;
}

//Changes the direction (in x pos) the Invader will move 
void Invader::ToggleDirection() {
    m_direction = static_cast<Direction>(!static_cast<bool>(m_direction));
}
