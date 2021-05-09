#pragma once
#include <cstdint>
#include <functional>

//Wrapper class for SDL_Renderer
enum RenderFlag { Fill = 1, OutLine = 2, Both = 3};
using CallBack = std::function<void(void)>;

class Window;
class Point2D;
class SDL_Renderer;
class Renderer {
public:
    Renderer(Window& window, int index = -1, uint32_t flags = 0);
    ~Renderer();
    void Clear();
    void Present();
    void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void DrawLine(const Point2D& start, const Point2D& end);
    void DrawLines(const std::vector<Point2D>& points);
    void DrawClosedPolygon(const std::vector<Point2D>& points);
    void FillShape(CallBack fillCB);
    void DrawOutLine(CallBack outLineCB);
    SDL_Renderer* GetSDLRenderer() const { return m_rendererSDL; }
private:
    //The window this renderer is drawing to
    Window& m_window;
    //the underlying sdl renderer
    SDL_Renderer* m_rendererSDL;
};