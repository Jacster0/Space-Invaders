#include "Projectile.h"
#include "Renderer.h"
#include <algorithm>

Projectile::Projectile(int posX, const std::shared_ptr<Renderer>& renderer)
    :
    m_rect({ posX,600 }, 255, 0, 0, 255, 25, 50, renderer)
{
}

void Projectile::Move(int speed) {
    int oldY = m_rect.GetPoint().y;
    Point2D newLoc = m_rect.GetPoint();
    newLoc.x -= 2 * speed;

    newLoc.y = std::max(0.0f,newLoc.y);
    m_rect.SetPoint(newLoc);
}

void Projectile::Draw() {
    m_rect.render(RenderFlag::Fill);
}
