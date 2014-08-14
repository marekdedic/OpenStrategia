#include "Main.hpp"
using namespace std;
using namespace glm;

RenderObject::RenderObject() : position(new mat4(1)), orientation(new mat4(1)), texture(new Texture("tank-tex.bmp")), VBO(0), VBOsize(0), UVBO(0), UVBOsize(0), EBO(0), EBOsize(0), IBO(0), IBOsize(0), indirectData(new DrawElementsIndirectCommand)
{
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &UVBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &IBO);
    indirectData->primCount = 1;
    indirectData->firstIndex = 0;
    indirectData->baseVertex = 0;
    indirectData->baseInstance = 0;
}

RenderObject::RenderObject(const RenderObject& other) : position(other.position), orientation(other.orientation), VBO(0), VBOsize(other.VBOsize), UVBO(0), UVBOsize(other.UVBOsize), EBO(0), EBOsize(other.EBOsize), IBO(0), IBOsize(other.IBOsize), indirectData(new DrawElementsIndirectCommand)
{
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_COPY_READ_BUFFER, VBO);
    glBindBuffer(GL_COPY_WRITE_BUFFER, other.VBO);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, VBOsize);
    glGenBuffers(1, &UVBO);
    glBindBuffer(GL_COPY_READ_BUFFER, UVBO);
    glBindBuffer(GL_COPY_WRITE_BUFFER, other.UVBO);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, UVBOsize);
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
        UVBO = 0;
        UVBOsize = other.UVBOsize;
        EBO = 0;
        EBOsize = other.EBOsize;
        IBO = 0;
        IBOsize = other.IBOsize;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_COPY_READ_BUFFER, VBO);
        glBindBuffer(GL_COPY_WRITE_BUFFER, other.VBO);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, VBOsize);
        glGenBuffers(1, &UVBO);
        glBindBuffer(GL_COPY_READ_BUFFER, UVBO);
        glBindBuffer(GL_COPY_WRITE_BUFFER, other.UVBO);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, UVBOsize);
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

RenderObject::RenderObject(std::vector<GLfloat>* vertexData, std::vector<GLuint>* indexData) : RenderObject()
{
    if((vertexData->size() % 3) != 0)
    {
        ERROR << "Invalid vertex data passed to RenderObject constructor" << endl;
        return;
    }
    if((indexData->size() % 3) != 0)
    {
        ERROR << "Invalid index data passed to RenderObject constructor" << endl;
        return;
    }
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexData->size() * sizeof(GLfloat), vertexData->data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData->size() * sizeof(GLuint), indexData->data(), GL_STATIC_DRAW);
	indirectData->elementCount = indexData->size();
}

void RenderObject::handle() {}
void RenderObject::update() {}

void RenderObject::render(const Program* const prg, const glm::mat4* const viewMatrix, const glm::mat4* const projectionMatrix) const
{
    // Compute Model matrix, send it to GLSL
    mat4 modelMatrix = *position * *orientation;
    GLuint loc = glGetUniformLocation(prg->programID, "modelMatrix");
    glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(modelMatrix));

    // Compute ModelViewProjection matrix, send it to GLSL
    mat4 MVP = *projectionMatrix * *viewMatrix * modelMatrix;
    loc = glGetUniformLocation(prg->programID, "MVP");
    glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(MVP));

    // Send light position to GLSL
    vec3 LightPosition = vec3(-3, 1, 5);
    loc = glGetUniformLocation(prg->programID, "lPosition_w");
    glUniform3fv(loc, 1, value_ptr(LightPosition));

    // Send light falloff distances to GLSL
    float LightFalloffMin = 1;
    loc = glGetUniformLocation(prg->programID, "lFalloffMin");
    glUniform1fv(loc, 1, &LightFalloffMin);
    float LightFalloffMax = 6;
    loc = glGetUniformLocation(prg->programID, "lFalloffMax");
    glUniform1fv(loc, 1, &LightFalloffMax);

    // Send camera position to GLSL
    loc = glGetUniformLocation(prg->programID, "cPosition_w");
    glUniform3fv(loc, 1, value_ptr(*MAINCAM->position));

    // Send the texture to Graphics card
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->textureID);

    // Use texture unit 0
    loc = glGetUniformLocation(prg->programID, "oSampler");
    glUniform1i(loc, 0);

    // Send the vertices to GLSL
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Send the UVs to GLSL
    glBindBuffer(GL_ARRAY_BUFFER, UVBO);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Send the render information to graphics
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, IBO);
	glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(*indirectData), indirectData, GL_STATIC_DRAW);

    // Draw from Draw Indirect Buffer Object
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER,  IBO);
	glDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, nullptr);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

RenderObject::~RenderObject()
{
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &UVBO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &IBO);
    delete position;
    delete orientation;
    delete indirectData;
}
