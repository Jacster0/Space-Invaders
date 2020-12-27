#include "Circle.h"
#include "SDL.h"
#include <iostream>

Circle::Circle(Point2D point, int radius)
    :
    Shape(point, 0u, 0u, 0u, 1u),
    radius(radius)
{}

int Circle::GetRadius() const {
    return radius;
}

void Circle::SetRadius(int value) {
    if (value < 0) {
        std::cout << "Radius cannot be negative!" << std::endl;
        return;
    }
    radius = value;
}

void Circle::render(SDL_Renderer* renderer) {
    std::cout << "Circle" << std::endl;
    std::cout << "Position:" << std::endl;
    std::cout << GetPoint().to_string() << std::endl;
    std::cout << "Radius: " << radius << std::endl;

    Point2D pt = GetPoint();
    //set the color
    SDL_SetRenderDrawColor(renderer, GetRed(), GetGreen(), GetBlue(), GetAlpha());

    int theta = 0;

    while (theta++ <= 360) {
        int x = GetRadius() * cos(theta);
        int y = GetRadius() * sin(theta);

        int screenPosX = x + pt.x;
        int screenPosY = y + pt.y;

        SDL_RenderDrawLine(renderer, screenPosX, screenPosY, screenPosX, screenPosY);
    }
}

