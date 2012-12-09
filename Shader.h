#ifndef SHADER_H
#define SHADER_H

#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#include <iostream>
#include <string>
#include <vector>

class Shader
{
public:
    Shader(){};
    GLuint CreateShader(GLenum shaderType, const std::string &strShaderFile);
    GLuint createProgram(std::vector<GLuint> &shaderList);
    static std::string* readTextFile(const char* filename);
private:
};
#endif
