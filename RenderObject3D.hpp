/**
 * @file RenderObject3D.hpp
 * File with RenderObject3D class
 * @author GenaBitu
 **/

#ifndef RENDEROBJECT3D_HPP
#define RENDEROBJECT3D_HPP
#include "Libs.hpp"

class RenderObject3D : public RenderObject
{
public:
    RenderObject3D();
    RenderObject3D(std::vector<GLfloat> vertexData, std::vector<GLuint> indexData);
    virtual void render(const Program* const shaders, const Camera* const cam) const;
};

 #endif // RENDEROBJECT3D_HPP
