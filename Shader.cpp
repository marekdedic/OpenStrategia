#include "Main.hpp"
using namespace std;
using namespace glm;

Shader::Shader(string name, GLenum shaderType) : shaderID(glCreateShader(shaderType))
{
    name = "shaders/" + name;
    string code;
    ifstream file(name);
    if(file.is_open())
    {
        string line;
        while(getline(file, line))
        {
            code += "\n" + line;
        }
        file.close();
    }
    GLchar const *codePtr = code.c_str();
    glShaderSource(shaderID, 1, &codePtr, NULL);
    glCompileShader(shaderID);
    GLint result;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    if(result != GL_TRUE)
    {
        int infoLogLength;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
        string errorMessage;
        glGetShaderInfoLog(shaderID, infoLogLength, NULL, &errorMessage[0]);
        error << "Error: " << errorMessage << ", when compiling shader: " << name << " of type: " << shaderType << endl;
        QUIT = true;
        return;
    }
}

Shader::~Shader()
{
    glDeleteShader(shaderID);
}
