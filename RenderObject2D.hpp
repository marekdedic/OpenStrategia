/**
 * @file RenderObject2D.hpp
 * File with RenderObject2D class
 * @author GenaBitu
 **/

#ifndef RENDEROBJECT2D_HPP
#define RENDEROBJECT2D_HPP
#include "Libs.hpp"

class RenderObject2D : public RenderObject
{
public:
    RenderObject2D();
    RenderObject2D(std::vector<GLfloat>* vertexData, std::vector<GLuint>* indexData);
    virtual void render(const Program* const shaders) const;
};

 #endif // RENDEROBJECT2D_HPP
