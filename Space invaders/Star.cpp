#include "Star.h"
#include "Renderer.h"
#include "SDL.h"
#include <numbers>

Star::Star(Point2D point, int innerRadius, int outerRadius, int flares, float blinkFrequncy, const std::shared_ptr<Renderer>& renderer)
    :
    m_blinkFrequncy(blinkFrequncy),
    m_renderer(renderer),
    Shape(point, 255,255,0,255)
{
    //The following algorithm for creating a star was learned by watching this youtube video
    //https://youtu.be/uHPl5pwAtFE?list=PLqCJpWy5Fohd6Hg5BW8eAjo5SzQQY0S&t=1

    const auto numPoints = flares * 2;
    //since we know that the numbers of points is just flares * 2 we can
    //we can call points.reserve with that number 
    m_points.reserve(numPoints);

    constexpr float pi = std::numbers::pi_v<float>;
    const auto theta = 2.0f * pi / static_cast<float>(numPoints);

    for (int i = 0; i < numPoints; i++) {
        const float radius = (i % 2 == 0) ? outerRadius : innerRadius;

        auto x = radius * cos(static_cast<float>(i) * theta);
        auto y = radius * sin(static_cast<float>(i) * theta);

        //transform to screen space
        auto screenPosX = x + point.x;
        auto screenPosY =  y + point.y;

        m_points.push_back({ x,y });
    }
}

void Star::render(RenderFlags renderFlags) {
    if ((renderFlags & RenderFlag::Fill) == RenderFlag::Fill) {
        throw std::exception("Star does not support the Renderflag::Fill mode");
    }

    m_renderer->SetColor(GetRed(),GetGreen(),GetBlue(),GetAlpha());

    //Transform to screen space
    for (auto& point : m_points) {
        point.x += Shape::GetPoint().x;
        point.y += Shape::GetPoint().y;
    }

    //Draw the star as a closed polygon
    m_renderer->DrawClosedPolygon(m_points);

    //Transform back to object space
    for (auto& point : m_points) {
        point.x -= Shape::GetPoint().x;
        point.y -= Shape::GetPoint().y;
    }
}

void Star::Scale(Star& star) {
    //Apply scaling
    auto points = star.GetPoints();

    for (auto& point : points) {
        point.x *= m_scale;
        point.y *= m_scale;
    }

    m_points = points;
}
