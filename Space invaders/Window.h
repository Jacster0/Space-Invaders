#pragma once
//Wrapper for the SDL_Window
class SDL_Window;
class Window {
public:
    static Window* Create();
    static void Destroy();
    static int GetWidth() noexcept  { return m_width; };
    static int GetHeight() noexcept { return m_height; }
    void Show() noexcept; 
    SDL_Window* GetSDLWindow() const { return m_windowSDL; }
private:
    Window(int width, int height);
    Window(const Window& rhs) = delete;
    Window& operator=(const Window& rhs) = delete;
    ~Window() = default;

    static Window* m_instance;
    SDL_Window* m_windowSDL;
    static constexpr int m_width = 800;
    static constexpr int m_height = 600;
};