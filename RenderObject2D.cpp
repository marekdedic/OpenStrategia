#include "Main.hpp"
using namespace std;
using namespace glm;

RenderObject2D::RenderObject2D() :RenderObject() {}

RenderObject2D::RenderObject2D(std::vector<GLfloat>* vertexData, std::vector<GLuint>* indexData) : RenderObject(vertexData, indexData) {}

void RenderObject2D::render(const Program* const prg) const
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
                        0, 0, 0, 1};
    GLint loc {glGetUniformLocation(prg->programID, "matrix")};
    glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(matrix));

    RenderObject::render(prg, 2);
    glEnable(GL_DEPTH_TEST);
}
