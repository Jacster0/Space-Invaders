#pragma once
//Wrapper for the SDL_Window
class SDL_Window;
class Window {
public:
    static Window* Create(int width = 800, int height = 600);
    static void Destroy();
    void Show() noexcept; 
    SDL_Window* GetSDLWindow() const { return m_windowSDL; }
private:
    Window(int width, int height);
    Window(const Window& rhs) = delete;
    Window& operator=(const Window& rhs) = delete;
    ~Window() = default;

    static Window* m_instance;
    SDL_Window* m_windowSDL;
    int m_width;
    int m_height;
};