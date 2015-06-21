#include "../Main.hpp"
using namespace std;
using namespace glm;

RenderObject::RenderObject() : position{new mat4{}}, orientation{new mat4{}}, VAO{}, VBO{}, UVBO{}, EBO{}
{
    // Create VAO, Bind all buffers to it
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Due to different vector sizes, glVertexAttribPointer() is called from child classes

    glGenBuffers(1, &UVBO);
    glBindBuffer(GL_ARRAY_BUFFER, UVBO);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBindVertexArray(0);
}

RenderObject::RenderObject(const RenderObject& other) : position{new mat4{*other.position}}, orientation{new mat4{*other.orientation}}, VAO{}, VBO{}, UVBO{}, EBO{}
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLint bufferSize{};
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_COPY_READ_BUFFER, other.VBO);
    glGetBufferParameteriv (GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &bufferSize);
    if(bufferSize > 0)
    {
        glBindBuffer(GL_COPY_WRITE_BUFFER, VBO);
        glBufferData(GL_COPY_WRITE_BUFFER, bufferSize, nullptr, GL_STATIC_DRAW);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, bufferSize);
    }

    glGenBuffers(1, &UVBO);
    glBindBuffer(GL_ARRAY_BUFFER, UVBO);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_COPY_READ_BUFFER, other.UVBO);
    glGetBufferParameteriv (GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &bufferSize);
    if(bufferSize > 0)
    {
        glBindBuffer(GL_COPY_WRITE_BUFFER, UVBO);
        glBufferData(GL_COPY_WRITE_BUFFER, bufferSize, nullptr, GL_STATIC_DRAW);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, bufferSize);
    }

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBindBuffer(GL_COPY_READ_BUFFER, other.EBO);
    glGetBufferParameteriv (GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &bufferSize);
    if(bufferSize > 0)
    {
        glBindBuffer(GL_COPY_WRITE_BUFFER, EBO);
        glBufferData(GL_COPY_WRITE_BUFFER, bufferSize, nullptr, GL_STATIC_DRAW);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, bufferSize);
    }

    glBindVertexArray(0);
}

RenderObject& RenderObject::operator=(const RenderObject& other)
{
    GLint bufferSize{};
    *position = *other.position;
    *orientation = *other.orientation;
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData->size() * sizeof(GLuint), indexData->data(), GL_STATIC_DRAW);
}

void RenderObject::handle() {}
void RenderObject::update() {}

void RenderObject::render(std::shared_ptr<Program> prg) const
{
    // Select shader program and VAO
    glUseProgram(prg->ID);
    glBindVertexArray(VAO);

    // Render the object
	int elementCount{0};
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &elementCount);
	glDrawElements(GL_TRIANGLES, elementCount/sizeof(GLuint), GL_UNSIGNED_INT, nullptr);

	glBindVertexArray(0);
}

RenderObject::~RenderObject()
{
    position.reset();
    orientation.reset();
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &UVBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}
