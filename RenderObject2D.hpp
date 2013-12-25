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
    virtual void render(const Program* const shaders) const;
private:
    static Camera* cam2D;
};

 #endif // RENDEROBJECT2D_HPP
