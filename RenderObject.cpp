#include "Main.hpp"
using namespace std;
using namespace glm;

RenderObject::RenderObject() : position(new mat4(1)), orientation(new mat4(1)), texture(new Texture("tank-tex.bmp")), VBO(0), UVBO(0), EBO(0), elementCount(0)
{
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &UVBO);
    glGenBuffers(1, &EBO);
}

RenderObject::RenderObject(const RenderObject& other) : position(new mat4(1)), orientation(new mat4(1)), texture(new Texture(*other.texture)), VBO(0), UVBO(0), EBO(0), elementCount(0)
{
    GLint bufferSize = 0;
    *position = *other.position;
    *orientation = *other.orientation;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_COPY_READ_BUFFER, other.VBO);
    glGetBufferParameteriv (GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &bufferSize);
    if(bufferSize > 0)
    {
        glBindBuffer(GL_COPY_WRITE_BUFFER, VBO);
        glBufferData(GL_COPY_WRITE_BUFFER, bufferSize, nullptr, GL_STATIC_DRAW);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, bufferSize);
    }
    glGenBuffers(1, &UVBO);
    glBindBuffer(GL_COPY_READ_BUFFER, other.UVBO);
    glGetBufferParameteriv (GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &bufferSize);
    if(bufferSize > 0)
    {
        glBindBuffer(GL_COPY_WRITE_BUFFER, UVBO);
        glBufferData(GL_COPY_WRITE_BUFFER, bufferSize, nullptr, GL_STATIC_DRAW);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, bufferSize);
    }
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_COPY_READ_BUFFER, other.EBO);
    glGetBufferParameteriv (GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &bufferSize);
    if(bufferSize > 0)
    {
        glBindBuffer(GL_COPY_WRITE_BUFFER, EBO);
        glBufferData(GL_COPY_WRITE_BUFFER, bufferSize, nullptr, GL_STATIC_DRAW);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, bufferSize);
    }
}

RenderObject& RenderObject::operator=(const RenderObject& other)
{
    GLint bufferSize = 0;
    *position = *other.position;
    *orientation = *other.orientation;
    *texture = *other.texture;
    glBindBuffer(GL_COPY_READ_BUFFER, other.VBO);
    glGetBufferParameteriv (GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &bufferSize);
    if(bufferSize > 0)
    {
        glBindBuffer(GL_COPY_WRITE_BUFFER, VBO);
        glBufferData(GL_COPY_WRITE_BUFFER, bufferSize, nullptr, GL_STATIC_DRAW);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, bufferSize);
    }
    glBindBuffer(GL_COPY_READ_BUFFER, other.UVBO);
    glGetBufferParameteriv (GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &bufferSize);
    if(bufferSize > 0)
    {
        glBindBuffer(GL_COPY_WRITE_BUFFER, UVBO);
        glBufferData(GL_COPY_WRITE_BUFFER, bufferSize, nullptr, GL_STATIC_DRAW);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, bufferSize);
    }
    glBindBuffer(GL_COPY_READ_BUFFER, other.EBO);
    glGetBufferParameteriv (GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &bufferSize);
    if(bufferSize > 0)
    {
        glBindBuffer(GL_COPY_WRITE_BUFFER, EBO);
        glBufferData(GL_COPY_WRITE_BUFFER, bufferSize, nullptr, GL_STATIC_DRAW);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, bufferSize);
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
	elementCount = indexData->size();
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

    // Draw from Element Buffer Object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, nullptr);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

RenderObject::~RenderObject()
{
    delete position;
    delete orientation;
    delete texture;
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &UVBO);
    glDeleteBuffers(1, &EBO);
}
