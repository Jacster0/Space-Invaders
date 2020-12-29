#pragma once
#include "Shape.h"
#include <memory>

//Using forward declarations to keep the header files clean
class Renderer;
class Circle : public Shape {
public:
    Circle(Point2D point, int radius);

    int GetRadius() const;
    void SetRadius(int value);

    void render(RenderFlags renderFlags) override;
private:
    std::shared_ptr<Renderer> m_renderer;
    int radius;
};

