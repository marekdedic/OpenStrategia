#include "Main.hpp"
using namespace std;
using namespace glm;

RenderObject::RenderObject() : position(mat4(1)), orientation(mat4(1)), VBO(0), VBOsize(0), EBO(0), EBOsize(0), IBO(0), IBOsize(0), indirectData(new DrawElementsIndirectCommand)
{
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &IBO);
    indirectData->primCount = 1;
    indirectData->firstIndex = 0;
    indirectData->baseVertex = 0;
    indirectData->baseInstance = 0;
}

RenderObject::RenderObject(const RenderObject& other) : position(other.position), orientation(other.orientation), VBO(0), VBOsize(other.VBOsize), EBO(0), EBOsize(other.EBOsize), IBO(0), IBOsize(other.IBOsize), indirectData(new DrawElementsIndirectCommand)
{
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_COPY_READ_BUFFER, VBO);
    glBindBuffer(GL_COPY_WRITE_BUFFER, other.VBO);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, VBOsize);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_COPY_READ_BUFFER, EBO);
    glBindBuffer(GL_COPY_WRITE_BUFFER, other.EBO);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, EBOsize);
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_COPY_READ_BUFFER, IBO);
    glBindBuffer(GL_COPY_WRITE_BUFFER, other.IBO);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, IBOsize);
    *indirectData = *(other.indirectData);
}

RenderObject& RenderObject::operator=(const RenderObject& other)
{
    if(this != &other)
    {
        position = other.position;
        orientation = other.orientation;
        VBO = 0;
        VBOsize = other.VBOsize;
        EBO = 0;
        EBOsize = other.EBOsize;
        IBO = 0;
        IBOsize = other.IBOsize;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_COPY_READ_BUFFER, VBO);
        glBindBuffer(GL_COPY_WRITE_BUFFER, other.VBO);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, VBOsize);
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_COPY_READ_BUFFER, EBO);
        glBindBuffer(GL_COPY_WRITE_BUFFER, other.EBO);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, EBOsize);
        glGenBuffers(1, &IBO);
        glBindBuffer(GL_COPY_READ_BUFFER, IBO);
        glBindBuffer(GL_COPY_WRITE_BUFFER, other.IBO);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, IBOsize);
        indirectData = new DrawElementsIndirectCommand;
        *indirectData = *(other.indirectData);
    }
    return *this;
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    /**< Get the render information to graphics */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, IBO);
	glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(*indirectData), indirectData, GL_STATIC_DRAW);

    /**< Draw from Draw Indirect Buffer Object */
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER,  IBO);
	glDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, nullptr);
	glDisableVertexAttribArray(0);
}

RenderObject::~RenderObject()
{
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &IBO);
    delete indirectData;
}
