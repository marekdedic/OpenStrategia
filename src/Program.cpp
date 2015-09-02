#include "../include/Main.hpp"
using namespace std;
using namespace glm;

Program::Program() : ID{glCreateProgram()}, shaders{} {}

void Program::addShader(const std::string name, const GLenum shaderType)
{
    shaders.emplace_back(new Shader(name, shaderType));
    glAttachShader(ID, shaders.back()->ID);
}

void Program::link() const
{
    glLinkProgram(ID);

    /**< Verify the result */
    GLint result{};
    glGetProgramiv(ID, GL_LINK_STATUS, &result);
    if(result != GL_TRUE) /**< Error */
    {
        int infoLogLength{};
        glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &infoLogLength);
        string errorMessage{};
        glGetProgramInfoLog(ID, infoLogLength, nullptr, &errorMessage[0]);
        ERROR << "Error: " << errorMessage << ", when linking Program: " << ID << endl;
        glfwSetWindowShouldClose(WINDOW, GL_TRUE);
        return;
    }
}

Program::~Program()
{
    for (auto& i : shaders)
    {
        i.reset();
    }
    shaders.clear();
    glDeleteProgram(ID);
}
