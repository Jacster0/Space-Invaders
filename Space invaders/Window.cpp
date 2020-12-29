#include "Window.h"
#include "SDL.h"

Window* Window::m_instance = nullptr;

Window* Window::Create(int width, int height) {
    if (m_instance) {
        return m_instance;
    }
    m_instance = new Window(width, height);
    return m_instance;
}

void Window::Destroy() {
    SDL_DestroyWindow(m_instance->m_windowSDL);
    m_instance->~Window();
    m_instance = nullptr;
}

void Window::Show() noexcept {
    SDL_ShowWindow(m_windowSDL);
}

Window::Window(int width, int height)
    :
    m_width(width),
    m_height(height)
{
    m_windowSDL = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_HIDDEN);
}