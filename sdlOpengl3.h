#include <SDL2/SDL.h>

class mainEngine
{
    private:
        SDL_Window* mainWindow;
        SDL_GLContext mainContext;

    public:

    mainEngine(){};

    SDL_Window* initSDL();

    SDL_GLContext initGL( SDL_Window* mainWindow);

    bool exitProgram(SDL_Window* window, SDL_GLContext* context);
};
