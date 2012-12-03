#include "Shader.h"
#include <stdio.h>

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
