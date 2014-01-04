/**
 * @file RenderObject.hpp
 * File with RenderObject class
 * @author GenaBitu
 **/

#ifndef RENDEROBJECT_HPP
#define RENDEROBJECT_HPP
#include "Libs.hpp"

typedef struct DrawElementsIndirectCommand_t
{
    GLuint  elementCount;
    GLuint  primCount;
    GLuint  firstIndex;
    GLuint  baseVertex;
    GLuint  baseInstance;
} DrawElementsIndirectCommand;

class RenderObject
{
public:
    glm::mat4 position;
    glm::mat4 orientation;
    RenderObject();
    RenderObject(const RenderObject& other);
    RenderObject& operator=(const RenderObject&);
    RenderObject(std::vector<GLfloat>* vertexData, std::vector<GLuint>* indexData);
    virtual void handle();
    virtual void update();
    virtual void render(const Program* const shaders, const glm::mat4* const viewMatrix, const glm::mat4* const projectionMatrix) const;
    virtual ~RenderObject();
protected:
    GLuint VBO;
    GLsizei VBOsize;
    GLuint EBO;
    GLsizei EBOsize;
    GLuint IBO;
    GLsizei IBOsize;
    DrawElementsIndirectCommand* indirectData;
};

 #endif // RENDEROBJECT_HPP
