#include "../include/RenderObject2D.hpp"

#include "../include/Program.hpp"
using namespace std;
using namespace glm;

RenderObject2D::RenderObject2D() : RenderObject()
{
    glBindVertexArray(VAO);

    // Set correct size for VBO vertices (2)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindVertexArray(0);
}

RenderObject2D::RenderObject2D(std::shared_ptr<std::vector<GLfloat>> vertexData, std::shared_ptr<std::vector<GLuint>> indexData) : RenderObject(vertexData, indexData) {}

void RenderObject2D::render(std::shared_ptr<Program> const prg) const
{
    glDisable(GL_DEPTH_TEST);

    // Select shader program and VAO
    glUseProgram(prg->ID);
    glBindVertexArray(VAO);

    // Change coordinate system
    mat4 matrix = mat4{ 1, 0, 0, 0,
                        0, 1, 0, 0,
                        0, 0, 1, 0,
                        -1, -1, 0, 1}
                 * mat4{2.0/SCREENSIZE.x, 0, 0, 0,
                        0, 2.0/SCREENSIZE.y, 0, 0,
                        0, 0, 1, 0,
                        0, 0, 0, 1} * *position * *orientation;
    GLint loc {glGetUniformLocation(prg->ID, "matrix")};
    glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(matrix));

    //Render the object
    RenderObject::render(prg);

    glBindVertexArray(0);
    glEnable(GL_DEPTH_TEST);
}
