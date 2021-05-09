#include "Window.h"
#include "SDL.h"

Window& Window::Create() {
    static Window instance;
    return instance;
}

Window::~Window() {
    SDL_DestroyWindow(m_windowSDL);
}

void Window::Show() noexcept {
    SDL_ShowWindow(m_windowSDL);
}

Window::Window() {
    m_windowSDL = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_HIDDEN);
}