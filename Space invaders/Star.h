#pragma once
#include "Shape.h"
#include <memory>
#include <vector>
#include "SDL.h"

class Star : public Shape {
public:
    Star(Point2D point, int innerRadius, int outerRadius, int flares, float blinkFrequncy, const std::shared_ptr<Renderer>& renderer);
    void render(RenderFlags renderFlags) override;
    void Scale(Star& points);

    void SetScale(float scale) noexcept { m_scale = scale; }
    float GetScale() const noexcept { return m_scale; }
    float GetBlinkFrequency() const noexcept { return m_blinkFrequncy; }

    std::vector<Point2D> GetPoints() const noexcept { return m_points; }
private:
    std::shared_ptr<Renderer> m_renderer;
    std::vector<Point2D> m_points;

    float m_scale = 1.0f;
    float m_blinkFrequncy{};
};
