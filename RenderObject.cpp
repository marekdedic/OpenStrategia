#include "Main.hpp"
using namespace std;
using namespace glm;

RenderObject::RenderObject() {}
void RenderObject::handle() {}
void RenderObject::update() {}

void RenderObject::render(const Program* const shaders, const mat4* const viewMatrix, const mat4* const projectionMatrix) const
{
    glUseProgram(shaders->programID);

    /**< Compute ModelViewProjection matrix, get it to GLSL */
    mat4 MVP = *projectionMatrix * *viewMatrix * position * orientation;
    GLuint MVPLoc = glGetUniformLocation(shaders->programID, "MVP");
    glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, &MVP[0][0]);

    /**< Get the information about the vertices to GLSL */
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    /**< Draw from indexed Vertex Buffer Object */
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  EBO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
	glDisableVertexAttribArray(0);
}

RenderObject::~RenderObject()
{
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
