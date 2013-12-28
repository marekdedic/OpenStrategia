#include "Main.hpp"
using namespace std;
using namespace glm;

RenderObject::RenderObject()
{
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &IBO);
    indirectData.primCount = 1;
    indirectData.firstIndex = 0;
    indirectData.baseVertex = 0;
    indirectData.baseInstance = 0;
}
void RenderObject::handle() {}
void RenderObject::update() {}

void RenderObject::render(const Program* const shaders, const glm::mat4* const viewMatrix, const glm::mat4* const projectionMatrix) const
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

    /**< Get the render information to graphics */
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, IBO);
	glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(indirectData), &indirectData, GL_STATIC_DRAW);

    /**< Draw from Draw Indirect Buffer Object */
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER,  IBO);
	glDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, (void*)0);
	glDisableVertexAttribArray(0);
}

RenderObject::~RenderObject()
{
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
