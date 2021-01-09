#include "Defender.h"
#include "Renderer.h"
#include "SDL_image.h"
#include <algorithm>
#include <iostream>

Defender::Defender(const std::shared_ptr<Renderer>& renderer)
    :
    m_renderer(renderer),
    m_rect({ 400, 750 }, 255, 0, 0, 255, 32, 32, renderer),
    m_projectile(std::make_shared<Projectile>(m_rect.GetPoint().x + m_rect.GetWidth()/2.0f, 700, renderer, 0, 255, 0))
{
    m_defenderTexture = IMG_LoadTexture(m_renderer->GetSDLRenderer(), R"(Resources\Textures\Defender.png)");
}

Defender::~Defender() {
    SDL_DestroyTexture(m_defenderTexture);
}

void Defender::Move(float step) {
    int oldX = m_rect.GetPoint().x;
    Point2D newLoc = m_rect.GetPoint();
    newLoc.x += step;

    //clamp the x position inside our screen coords
    newLoc.x = std::clamp(newLoc.x, 0.0f, 800.0f- m_rect.GetWidth());
    m_rect.SetPoint(newLoc);

    //update the projetiles x position if it is not launched
    if (!m_projectileIsLaunched) {
        //make it launch the projectile from the middle of the Defender rectangle
        const auto pos = newLoc.x + m_rect.GetWidth() / 2.0f;
        m_projectile->SetXPos(pos);
    }
}

void Defender::Draw() {
    SDL_Rect rect = { m_rect.GetPoint().x,m_rect.GetPoint().y, m_rect.GetWidth(), m_rect.GetHeight() };
    SDL_RenderCopy(m_renderer->GetSDLRenderer(), m_defenderTexture, nullptr, &rect);
}

void Defender::Shoot() noexcept {
    m_projectileIsLaunched = true;
}

//Resets the projectiles state and position
void Defender::ResetProjectile() {
    auto loc = m_rect.GetPoint();
    
    //make the projectile x coord to be in the middle of the Defender rectangle
    const auto pos = loc.x + m_rect.GetWidth() / 2.0f;
    m_projectile->SetXPos(pos);

    m_projectileIsLaunched = false;
}

//Resets the defender to a non-hit state
void Defender::ResetHit() {
    m_isHit = false;
}

void Defender::Reset() {
    m_rect.SetPoint({ 400, 750 });
    ResetProjectile();
    ResetHit();
}

std::shared_ptr<Projectile> Defender::GetProjectile() const noexcept {
    return m_projectile;
}

bool Defender::GetProjectileIsLaunched() const noexcept {
    return m_projectileIsLaunched;
}

const Rectangle& Defender::GetRectangle() const noexcept {
    return m_rect;
}

//Defender has been hit by an enemy projectile
void Defender::Hit() noexcept {
    m_isHit = true;
}

bool Defender::IsHit() const noexcept {
    return m_isHit;
}
