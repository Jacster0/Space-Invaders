#include "Invader.h"
#include "Renderer.h"
#include <algorithm>

Invader::Invader(const std::shared_ptr<Renderer>& renderer, float width, float height, float xCoord, float yCoord, Level level)
    :
    m_alienLevel(level),
    m_rect({ xCoord,yCoord }, 255,255,255,255, width, height, renderer),
    m_projectile(std::make_shared<Projectile>(xCoord, yCoord, renderer,255,0,0))
{
}

void Invader::Draw() {
    m_rect.render(RenderFlag::Fill);
}

//Moves the invader in X direction
void Invader::Move(int step) {
    int oldX = m_rect.GetPoint().x;
    float screenCoordMax = 800.0f - m_rect.GetWidth();
    Point2D newLoc = m_rect.GetPoint();

    if (m_direction == Direction::Right) {
        newLoc.x += step;
    }
    else {
        newLoc.x -= step;
    }
   
    //clamp the x position inside our screen coords
    newLoc.x = std::clamp(newLoc.x, 0.0f, screenCoordMax);
    m_rect.SetPoint(newLoc);

    //update the projetiles x position if it is not launched
    if (!projectileIsLaunched) {
        //make it launch the projectile from the middle of the Defender rectangle
        const auto xPos = newLoc.x + m_rect.GetWidth() / 2.0f;
        m_projectile->SetPos(xPos, newLoc.y + m_rect.GetHeight());
    }
}

//Moves the Invader in Y direction
void Invader::MoveY(int step) {
    int oldX = m_rect.GetPoint().y;
    float screenCoordMin = 850 - m_rect.GetHeight();
    Point2D newLoc = m_rect.GetPoint();

    newLoc.y += step;
   
    //clamp the y position inside our screen coords
    newLoc.y = std::clamp(newLoc.y, 0.0f, screenCoordMin);
    m_rect.SetPoint(newLoc);

}

//Resets the projectiles state and position
void Invader::ResetProjectile() {
    auto loc = m_rect.GetPoint();

    //make the projectile x coord to be in the middle of the Defender rectangle
    const auto xPos = loc.x + m_rect.GetWidth() / 2.0f;
    m_projectile->SetPos(xPos, loc.y + m_rect.GetHeight());

    projectileIsLaunched = false;
}

void Invader::SetLevel(Level level) noexcept {
    m_alienLevel = level;
}

Level Invader::GetLevel() const noexcept {
    return m_alienLevel;
}

void Invader::Shoot() {
    projectileIsLaunched = true;
}

void Invader::SetDirection(Direction direction) {
    m_direction = direction;
}

void Invader::Kill() {
    m_isDead = true;
}

void Invader::Revive() {
    m_isDead = false;
}

const Rectangle& Invader::GetRectangle() const {
    return m_rect;
}

Rectangle& Invader::GetRectangle() {
    return m_rect;
}

//Changes the direction (in x pos) the Invader will move 
void Invader::ToggleDirection() {
    m_direction = static_cast<Direction>(!static_cast<bool>(m_direction));
}
