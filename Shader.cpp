#include "Main.hpp"
using namespace std;
using namespace glm;

Shader::Shader(std::string name, const GLenum shaderType) : shaderID(glCreateShader(shaderType))
{
    /**< Load the shader code from the file */
    name = "shaders/" + name;
    string code;
    ifstream file(name);
    if(!file.is_open())
    {
        ERROR << "Failed to load shader: " << name << endl;
        glfwSetWindowShouldClose(WINDOW, GL_TRUE);
        return;
    }
    string line;
        while(getline(file, line))
        {
            code += "\n" + line;
        }
        file.close();
    GLchar const *codePtr = code.c_str();

    /**< Handle the code to OpenGL and compile it */
    glShaderSource(shaderID, 1, &codePtr, nullptr);
    glCompileShader(shaderID);

    /**< Verify the result */
    GLint result;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    if(result != GL_TRUE) /**< Error */
    {
        int infoLogLength;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
        string errorMessage;
        glGetShaderInfoLog(shaderID, infoLogLength, nullptr, &errorMessage[0]);
        ERROR << "Error: " << errorMessage << ", when compiling shader: " << name << " of type: " << shaderType << endl;
        glfwSetWindowShouldClose(WINDOW, GL_TRUE);
        return;
    }
}

Shader::~Shader()
{
    glDeleteShader(shaderID);
}
