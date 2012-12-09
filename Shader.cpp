#include "Shader.h"
#include <stdio.h>
#include <stdlib.h>


/*********************************
Shader::readTextFile

Copied from my assignment
Reads in a text file to use as
a shader source file
*********************************/
std::string* Shader::readTextFile(const char* filename)
{
    char* readText = NULL;
    std::string* readString = NULL;

    if(filename != NULL)
    {
        FILE* textFile = fopen(filename, "r");

        if( textFile != NULL)
        {
            fseek(textFile, 0, SEEK_END);
            int count = ftell(textFile);
            rewind(textFile);

            if(count > 0)
            {
                readText = (char*)malloc(sizeof(char) * (count + 1));
                count = fread(readText, sizeof(char), count, textFile);
                readText[count] = '\0'; //set last character to null terminator
                readString = new std::string(readText);
                delete[] readText;
            }

            fclose(textFile);

        }
        else
        {
            printf("Shader.readTextFile:Failed to open %s\n", filename);
        }
    }
    else
    {
        printf("Shader.readTextFile filename passed was null\n");
    }

    return readString;
}

//Takes in a type of shader and the shader string
//then compiles and checks for errors
GLuint Shader::CreateShader(GLenum shaderType, const std::string &strShaderFile)
{
    GLuint shader = glCreateShader(shaderType);
    const char* fileData = strShaderFile.c_str();
    glShaderSource(shader, 1, &fileData, NULL);

    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if( status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar* infoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);

        char* shaderTypeString;
        switch(shaderType)
        {
            case GL_VERTEX_SHADER:
                shaderTypeString = "vertex";
                break;
            case GL_GEOMETRY_SHADER:
                shaderTypeString = "geometry";
                break;
            case GL_FRAGMENT_SHADER:
                shaderTypeString = "fragment";
                break;
        }

        fprintf(stderr, "Compile failed in %s shader \n%s\n", shaderTypeString, infoLog);
        delete[] infoLog;
    }

    return shader;
}

GLuint Shader::createProgram(std::vector<GLuint> &shaderList)
{
    GLuint program = glCreateProgram();

    for(size_t i = 0; i < shaderList.size(); i++)
    {
        glAttachShader(program, shaderList[i]);
    }

    glLinkProgram(program);

    GLint status;
    glGetProgramiv( program, GL_INFO_LOG_LENGTH, &status);

    if(status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar* infoLog = new GLchar[infoLogLength];
        glGetProgramInfoLog(program, infoLogLength, NULL, infoLog);
        fprintf(stderr, "Linker failure: %s\n", infoLog);
        delete[] infoLog;
    }

    for(size_t i = 0; i < shaderList.size(); i++)
    {
        glDetachShader(program, shaderList[i]);
    }

    return program;
}
