#include "Renderer.h"
#include "SDL.h"
#include "Window.h"
#include "Point2D.h"

Renderer::Renderer(Window& window, int index, uint32_t flags)
    :
    m_window(window)
{
   m_renderer = SDL_CreateRenderer(m_window.Get(), index, flags);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_renderer);
}

void Renderer::Clear() {
    SDL_RenderClear(m_renderer);
}

void Renderer::Present() {
    SDL_RenderPresent(m_renderer);
}

void Renderer::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
}

void Renderer::DrawLine(const Point2D& start, const Point2D& end)
{
    SDL_RenderDrawLine(m_renderer, start.x, start.y, end.x, end.y);
}
