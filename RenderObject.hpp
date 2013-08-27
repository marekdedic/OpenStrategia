/**
 * @file RenderObject.hpp
 * File with RenderObject class
 * @author GenaBitu
 **/

#ifndef RENDEROBJECT_HPP
#define RENDEROBJECT_HPP
#include "Libs.hpp"

class RendObj
{
public:
    glm::vec4 position;
    RendObj();
    virtual void handle();
    virtual void update();
    virtual void render() const = 0;
    virtual ~RendObj();
protected:
    GLuint VBO;
};

 #endif // RENDEROBJECT_HPP
