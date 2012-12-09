#include "sdlOpengl3.h"
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <sstream>
#include <string>

#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

int main(int argc, char* argv[] )
{

    Engine engine;

    engine.initialise(argc, argv);

	return 0;
}

const std::string strVertexShader(
	"#version 330\n"
	"layout(location = 0) in vec4 position;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = position;\n"
	"}\n"
);

const std::string strFragmentShader(
	"#version 330\n"
	"out vec4 outputColor;\n"
	"void main()\n"
	"{\n"
	"   outputColor = vec4(0.0f, 1.0f, 1.0f, 1.0f);\n"
	"}\n"
);

const float vertexPositions[] = {
	0.75f, 0.75f, 0.0f, 1.0f,
	0.75f, -0.75f, 0.0f, 1.0f,
	-0.75f, -0.75f, 0.0f, 1.0f,
};

Engine::Engine()
{
    quit = false;
}

void Engine::initialise( int argc, char** argv)
{
    initSDL();
    initGL();
    initShaders();

    initVertexBuffers();

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    mainEngine();
}

void Engine::initVertexBuffers()
{
    glGenBuffers(1, &positionBufferObject);

    glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Engine::initShaders()
{
     std::vector<GLuint> shaderList;
    Shader theShader;

    shaderList.push_back(theShader.CreateShader(GL_VERTEX_SHADER, strVertexShader));
    shaderList.push_back(theShader.CreateShader(GL_FRAGMENT_SHADER, strFragmentShader));

    glProgram = theShader.createProgram(shaderList);

    std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
}

void Engine::mainEngine()
{
    fpsTimer.start();
    int frames = 0;

    while(!quit)
    {
        handleEvents();

        frames++;

        drawFrame();

        if(fpsTimer.getTicks() > 1000)
        {
            std::stringstream caption;

            //Calculate the frames per second and create the string
            caption << "Average Frames Per Second: " << frames / ( fpsTimer.getTicks() / 1000.f );
            SDL_SetWindowTitle( mainWindow, caption.str().c_str());
            fpsTimer.start();
            frames = 0;
        }


    }
}

bool Engine::initSDL()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Unable to init SDL video subsystem\n");
		SDL_Quit();
		exit(1);
	}

	this->mainWindow = SDL_CreateWindow( "Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );

	if(!this->mainWindow)
	{
		printf( "Failed to create the main window\n");
	}

    return true;
}

bool Engine::initGL()
{
    SDL_GLContext* context = (SDL_GLContext*)malloc( sizeof(SDL_GLContext));
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    (*context) = SDL_GL_CreateContext(mainWindow);

	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f);
	glClear( GL_COLOR_BUFFER_BIT );

	glViewport(0, 0, (GLsizei) 640, (GLsizei) 480);

	int glContextVersion[2];

	glGetIntegerv( GL_MAJOR_VERSION, &glContextVersion[0] );
	glGetIntegerv( GL_MINOR_VERSION, &glContextVersion[1] );

	printf("Opengl context Major version:%d Minor:%d\n", glContextVersion[0], glContextVersion[1]);


	return *context;
}

bool Engine::exitProgram()
{
    bool retVal = false; //be pessimistic and assume it'll fail by default

    glDeleteProgram(glProgram);
    glDeleteBuffers(1, &positionBufferObject);
    glDeleteVertexArrays(1, &vao);

	SDL_GL_DeleteContext(mainContext);  //not sure if it safe to call this if the context is not initialised have to ask about it. Nothing on the wiki
	SDL_DestroyWindow(mainWindow);      //also not sure about this one either.
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

void Engine::handleEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                quit = true;
            break;
            case SDL_WINDOWEVENT_RESIZED:
                handleResize(event.window.data1, event.window.data2);
                break;
            default:
            break;
        }
    }
}

void Engine::handleResize(int width, int height)
{
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
}

void Engine::drawFrame()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(glProgram);

    glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays( GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);
    glUseProgram(0);

    SDL_GL_SwapWindow(mainWindow);
}


