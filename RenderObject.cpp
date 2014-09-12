#include "Main.hpp"
using namespace std;
using namespace glm;

RenderObject::RenderObject() : position{new mat4{}}, orientation{new mat4{}}, texture{new Texture{}}, VBO{}, UVBO{}, EBO{}
{
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &UVBO);
    glGenBuffers(1, &EBO);
}

RenderObject::RenderObject(const RenderObject& other) : position{new mat4{*other.position}}, orientation{new mat4{*other.orientation}}, texture{new Texture{*other.texture}}, VBO{}, UVBO{}, EBO{}
{
    GLint bufferSize{};
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
    GLint bufferSize{};
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

RenderObject::RenderObject(std::shared_ptr<std::vector<GLfloat>> vertexData, std::shared_ptr<std::vector<GLuint>> indexData) : RenderObject()
{
    if(((vertexData->size() % 3) != 0) or ((vertexData->size() % 2) != 0))
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
}

void RenderObject::handle() {}
void RenderObject::update() {}

void RenderObject::render(std::shared_ptr<Program> prg, const GLint vecSize, const GLint texUnit) const
{
    // Send the 0th texture to Graphics card
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->textureID);

    // Use texture unit 0
    GLint loc{glGetUniformLocation(prg->programID, "oSampler")};
    glUniform1i(loc, texUnit);

    // Send the vertices to GLSL
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, vecSize, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Send the UVs to GLSL
    glBindBuffer(GL_ARRAY_BUFFER, UVBO);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Draw from Element Buffer Object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    int elementCount{0};
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &elementCount);
	glDrawElements(GL_TRIANGLES, elementCount/sizeof(GLuint), GL_UNSIGNED_INT, nullptr);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

RenderObject::~RenderObject()
{
    position.reset();
    orientation.reset();
    texture.reset();
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &UVBO);
    glDeleteBuffers(1, &EBO);
}
