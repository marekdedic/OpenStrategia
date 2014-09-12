#include "Main.hpp"
using namespace std;
using namespace glm;

RenderObject2D::RenderObject2D() : RenderObject() {}

RenderObject2D::RenderObject2D(std::shared_ptr<std::vector<GLfloat>> vertexData, std::shared_ptr<std::vector<GLuint>> indexData) : RenderObject(vertexData, indexData) {}

void RenderObject2D::render(std::shared_ptr<Program> const prg, const GLint texUnit) const
{
    glDisable(GL_DEPTH_TEST);

    // Select shader program
    glUseProgram(prg->programID);

    // Change coordinate system
    mat4 matrix = mat4{ 1, 0, 0, 0,
                        0, 1, 0, 0,
                        0, 0, 1, 0,
                        -1, -1, 0, 1}
                 * mat4{2.0/WIDTH, 0, 0, 0,
                        0, 2.0/HEIGHT, 0, 0,
                        0, 0, 1, 0,
                        0, 0, 0, 1} * *position * *orientation;
    GLint loc {glGetUniformLocation(prg->programID, "matrix")};
    glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(matrix));

    RenderObject::render(prg, 2, texUnit);
    glEnable(GL_DEPTH_TEST);
}
