#include "Main.hpp"
using namespace std;
using namespace glm;

Program::Program() : programID(glCreateProgram()) {}

void Program::AddShader(std::string name, GLenum shaderType)
{
    shaders.push_back(new Shader(name, shaderType));
    glAttachShader(programID, shaders.back()->shaderID);
}

void Program::Link()
{
    glLinkProgram(programID);
    GLint result;
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    if(result != GL_TRUE)
    {
        int infoLogLength;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
        string errorMessage;
        glGetProgramInfoLog(programID, infoLogLength, NULL, &errorMessage[0]);
        error << "Error: " << errorMessage << ", when linking Program: " << programID << endl;
        QUIT = true;
        return;
    }
}

Program::~Program()
 {
     glDeleteProgram(programID);
 }
