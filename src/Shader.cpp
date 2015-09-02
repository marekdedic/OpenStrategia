#include "../include/Program.hpp"
using namespace std;
using namespace glm;

Program::Shader::Shader(std::string name, const GLenum shaderType) : ID{glCreateShader(shaderType)}
{
    /**< Load the shader code from the file */
    name = "shaders/" + name;
    string code{};
    ifstream file{name};
    if(!file.is_open())
    {
        ERROR << "Failed to load shader: " << name << endl;
        glfwSetWindowShouldClose(WINDOW, GL_TRUE);
        return;
    }
    string line{};
        while(getline(file, line))
        {
            code += "\n" + line;
        }
        file.close();
    GLchar const* codePtr{code.c_str()};

    /**< Handle the code to OpenGL and compile it */
    glShaderSource(ID, 1, &codePtr, nullptr);
    glCompileShader(ID);

    /**< Verify the result */
    GLint result{};
    glGetShaderiv(ID, GL_COMPILE_STATUS, &result);
    if(result != GL_TRUE) /**< Error */
    {
        int infoLogLength{};
        glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &infoLogLength);
        string errorMessage{};
        glGetShaderInfoLog(ID, infoLogLength, nullptr, &errorMessage[0]);
        ERROR << "Error: " << errorMessage << ", when compiling shader: " << name << " of type: " << shaderType << endl;
        glfwSetWindowShouldClose(WINDOW, GL_TRUE);
        return;
    }
}

Program::Shader::~Shader()
{
    glDeleteShader(ID);
}
