#ifndef SDL_OPENGL3_H
#define SDL_OPENGL3_H

#include <SDL2/SDL.h>
#include "Shader.h"
#include "timer.h"

class Engine
{
    private:
        SDL_Window* mainWindow;
        SDL_GLContext mainContext;
        GLuint glProgram;
        GLuint positionBufferObject;
        GLuint vao;         //vertex array object
        Timer fpsTimer;

        bool quit;

    public:

    Engine();

    void mainEngine();

    void initialise( int argc, char** argv);

    void initVertexBuffers();

    void initShaders();

    bool initSDL();

    bool initGL();

    void handleEvents();

    void handleResize(int width, int height);

    void drawFrame();

    bool exitProgram();
};
#endif
