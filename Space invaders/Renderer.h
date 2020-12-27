#pragma once
#include <cstdint>
//Wrapper class for SDL_Renderer
class Window;
class Point2D;
class SDL_Renderer;
class Renderer {
public:
    Renderer(Window& window, int index, uint32_t flags);
    ~Renderer();
    void Clear();
    void Present();
    void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void DrawLine(const Point2D& start, const Point2D& end);
private:
    //The window this renderer is drawing to
    Window& m_window;
    //the underlying sdl renderer
    SDL_Renderer* m_renderer;
};