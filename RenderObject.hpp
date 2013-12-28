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
    GLuint  count;
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
    virtual void handle();
    virtual void update();
    virtual void render(const Program* const shaders, const glm::mat4* const viewMatrix, const glm::mat4* const projectionMatrix) const;
    ~RenderObject();
protected:
    GLuint VBO;
    GLuint EBO;
    DrawElementsIndirectCommand indirectData;
    GLuint IBO;
};

 #endif // RENDEROBJECT_HPP
