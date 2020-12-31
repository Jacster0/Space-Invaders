#include "Defender.h"
#include "Renderer.h"
#include <algorithm>
#include <iostream>

Defender::Defender(const std::shared_ptr<Renderer>& renderer)
    :
    rect({ 400, 550 }, 255, 0, 0, 255, 50, 50, renderer),
    m_projectile(std::make_unique<Projectile>(rect.GetPoint().x, renderer))
{

}

void Defender::Move(int speed) {
    int oldX = rect.GetPoint().x;
    Point2D newLoc = rect.GetPoint();
    newLoc.x += speed;

    //clamp the x position inside our screen coords
    newLoc.x = std::clamp(newLoc.x, 0.0f, 800.0f- rect.GetWidth());
    rect.SetPoint(newLoc);

    //update the projetiles x position if it is not launched
    if (!projectileIsLaunched) {
        //make it launch the projectile from the middle of the Defender rectangle
        const auto pos = newLoc.x + rect.GetWidth() / 2.0f;
        m_projectile->SetXPos(pos);
    }
}

void Defender::Draw() {
    rect.render(RenderFlag::Fill);

    if (projectileIsLaunched) {
        m_projectile->Draw();
        m_projectile->Move(1);
    }
}

void Defender::Shoot() noexcept {
    projectileIsLaunched = true;
}
