#include "Defender.h"
#include "Renderer.h"
#include <algorithm>

Defender::Defender(const std::shared_ptr<Renderer>& renderer)
    :
    rect({ 400, 550 }, 255, 0, 0, 255, 50, 50, renderer)
{

}

void Defender::Move(int speed) {
    int oldX = rect.GetPoint().x;
    Point2D newLoc = rect.GetPoint();
    newLoc.x += 2 * speed;

    newLoc.x = std::clamp(newLoc.x, 0.0f, 800.0f- rect.GetWidth());
    rect.SetPoint(newLoc);
}

void Defender::Draw() {
    rect.render(RenderFlag::Fill);
}

void Defender::Shoot() {
}
