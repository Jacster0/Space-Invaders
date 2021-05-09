#include "Renderer.h"
#include "SDL.h"
#include "Window.h"
#include "Point2D.h"

Renderer::Renderer(Window& window, int index, uint32_t flags)
    :
    m_window(window)
{
   m_rendererSDL = SDL_CreateRenderer(m_window.GetSDLWindow(), index, flags);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_rendererSDL);
}

void Renderer::Clear() {
    SDL_RenderClear(m_rendererSDL);
}

void Renderer::Present() {
    SDL_RenderPresent(m_rendererSDL);
}

void Renderer::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    SDL_SetRenderDrawColor(m_rendererSDL, r, g, b, a);
}

void Renderer::DrawLine(const Point2D& start, const Point2D& end)
{
    SDL_RenderDrawLine(m_rendererSDL, start.x, start.y, end.x, end.y);
}

void Renderer::DrawLines(const std::vector<Point2D>& points) {
    SDL_RenderDrawLinesF(
        m_rendererSDL,
        reinterpret_cast<const SDL_FPoint*>(points.data()),
        points.size());
}

void Renderer::DrawClosedPolygon(const std::vector<Point2D>& points) {
    //Draw some connected lines to form the polygon
    this->DrawLines(points);
    //Connect the first point with the last so that we get a closed polygon
    this->DrawLine(points.front(), points.back());
}

void Renderer::FillShape(CallBack fillCB) {
    fillCB();
}

void Renderer::DrawOutLine(CallBack outLineCB) {
    outLineCB();
}
