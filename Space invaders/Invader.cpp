#include "Invader.h"
#include "Renderer.h"

#include <algorithm>

Invader::Invader(const std::shared_ptr<Renderer>& renderer, float width, float height, float xCoord, float yCoord)
    :
    m_rect({ xCoord,yCoord }, 255,255,255,255, width, height, renderer),
    m_projectile(std::make_unique<Projectile>(xCoord, yCoord, renderer))
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

//Moves the invader in X direction
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
    newLoc.x = std::clamp(newLoc.x, 0.0f, screenCoordMax);
    m_rect.SetPoint(newLoc);
}

//Moves the Invader in Y direction
void Invader::MoveY() {
    int oldX = m_rect.GetPoint().y;
    float screenCoordMin = 600 - m_rect.GetHeight();
    Point2D newLoc = m_rect.GetPoint();

    newLoc.y += speedY;
   
    //clamp the y position inside our screen coords
    newLoc.y = std::clamp(newLoc.y, 0.0f, screenCoordMin);
    m_rect.SetPoint(newLoc);
}

void Invader::Shoot() {
    projectileIsLaunched = true;
    m_projectile->Move(2);
}

void Invader::SetDirection(Direction direction) {
    m_direction = direction;
}

Rectangle Invader::GetRectangle() {
    return m_rect;
}

//Changes the direction (in x pos) the Invader will move 
void Invader::ToggleDirection() {
    m_direction = static_cast<Direction>(!static_cast<bool>(m_direction));
}
