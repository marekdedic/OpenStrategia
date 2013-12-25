/**
 * @file RenderObject.hpp
 * File with RenderObject class
 * @author GenaBitu
 **/

#ifndef RENDEROBJECT_HPP
#define RENDEROBJECT_HPP
#include "Libs.hpp"

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
    GLsizei EBOsize;
};

 #endif // RENDEROBJECT_HPP
