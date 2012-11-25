#include "sdlOpengl3.h"
#include <stdio.h>
#include <stdlib.h>

#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

int main(int argc, char* argv[] )
{

    mainEngine engine;

    engine.initSDL();
    engine.initGL();


	SDL_GL_SwapWindow(mainWindow);

	SDL_Delay(500);

	return engine.exitProgram(mainWindow, &mainContext);
}

bool mainEngine::initSDL()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Unable to init SDL video subsystem\n");
		SDL_Quit();
		exit(1);
	}

	this.window = SDL_CreateWindow( "Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
	printf("initSDL error:%s\n", SDL_GetError());
	SDL_ClearError();

	if(!this.window)
	{
		printf( "Failed to create the main window\n");
	}

    return true;
}

bool mainEngine::initGL()
{
    SDL_GLContext* context = (SDL_GLContext*)malloc( sizeof(SDL_GLContext));
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    (*context) = SDL_GL_CreateContext(mainWindow);

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f);
	glClear( GL_COLOR_BUFFER_BIT );

	int glContextVersion[2];

	glGetIntegerv( GL_MAJOR_VERSION, &glContextVersion[0] );
	glGetIntegerv( GL_MINOR_VERSION, &glContextVersion[1] );

	printf("Opengl context Major version:%d Minor:%d\n", glContextVersion[0], glContextVersion[1]);


	return *context;
}

bool mainEngine::exitProgram(SDL_Window* window, SDL_GLContext* context)
{
    bool retVal = false; //be pessimistic and assume it'll fail by default

	SDL_GL_DeleteContext(*context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	const char* error = SDL_GetError();

	if(strcmp(error, "") == 0)
	{
	    retVal = true;
	}
	else
	{
	    printf("exitProgram: Something went wrong somewhere or we forgot to clear SDL_Errors \"%s\"\n",error);
	}
	return retVal;
}

void handleEvents(SDL_Event* events)
{

}


