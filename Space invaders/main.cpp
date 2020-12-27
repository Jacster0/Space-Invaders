#include "SDL.h"
#include "Window.h"
#include "Renderer.h"

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_EVERYTHING);

    Window* wnd = Window::Create();
    wnd->Show();

    {
        Renderer renderer(*wnd, -1, 0);
        renderer.SetColor(0, 255, 0, 255);
        renderer.Clear();
        renderer.Present();
       
        SDL_Delay(50000);
    }

    Window::Destroy();
    SDL_Quit();
    return 0;
}