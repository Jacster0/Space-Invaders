#include "Rectangle.h"
#include "Renderer.h"
#include "SDL.h"
#include <iostream>

Rectangle::Rectangle(Point2D point, uint8_t r, uint8_t g, uint8_t b, uint8_t a, int width, int height, const std::shared_ptr<Renderer>& renderer)
    :
    Shape(point, r, g, b, a),
    width(width),
    height(height),
    m_renderer(renderer)
{}

int Rectangle::GetWidth() const {
    return width;
}

int Rectangle::GetHeight() const {
    return height;
}

void Rectangle::SetWidth(int value) {
    if (value < 0) {
        std::cout << "Width cannot be negative!" << std::endl;
        return;
    }
    width = value;
}

void Rectangle::SetHeight(int value) {
    if (value < 0) {
        std::cout << "Height cannot be negative!" << std::endl;
        return;
    }
    height = value;
}

void Rectangle::render(RenderFlags renderFlags) {
    std::cout << "Rectangle" << std::endl;
    std::cout << "Position:" << std::endl;
    std::cout << GetPoint().to_string() << std::endl;
    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;

    Point2D pt = GetPoint();
    //set the color
    m_renderer->SetColor(GetRed(), GetGreen(), GetBlue(), GetAlpha());
    //calculate the start and end screen coords
    int startX = pt.x;
    int endX = pt.x + width;

    int startY = pt.y;
    int endY = pt.y + height;

    SDL_Rect rect;
    rect.x = startX;
    rect.y = startY;
    rect.w = width;
    rect.h = height;

    if ((renderFlags & RenderFlag::Fill) == RenderFlag::Fill) {
        m_renderer->FillShape([&]() {SDL_RenderFillRect(m_renderer->GetSDLRenderer(), &rect); });
    }
    if ((renderFlags & RenderFlag::OutLine) == RenderFlag::OutLine) {
        
        //If we are also drawing a filled shape, draw the outline with the inverted color
        if ((renderFlags & RenderFlag::Fill) == RenderFlag::Fill) {
            m_renderer->SetColor(~GetRed(), ~GetGreen(), ~GetBlue(), GetAlpha());
        }

        //draw the outline of the shape
        //Horizontal lines
        m_renderer->DrawOutLine([&]() {
            m_renderer->DrawLine(Point2D(startX, startY), Point2D(endX, startY));
            m_renderer->DrawLine(Point2D(startX, endY), Point2D(endX, endY));

            //vertical lines
            m_renderer->DrawLine(Point2D(startX, startY), Point2D(startX, endY));
            m_renderer->DrawLine(Point2D(endX, startY), Point2D(endX, endY));
            });
    }
}
