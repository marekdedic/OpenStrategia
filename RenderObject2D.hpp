/**
 * \file RenderObject2D.hpp
 * \brief File with RenderObject2D class
 * \author GenaBitu
 **/

#ifndef RENDEROBJECT2D_HPP
#define RENDEROBJECT2D_HPP
#include "Libs.hpp"

/** \brief RenderObject2D class
 *
 * This class further develops the functionality of RenderObject to target 2D objects only.
 */
class RenderObject2D : public RenderObject
{
public:
    RenderObject2D();
    /** \brief RenderObject2D constructor
     *
     * Creates an 2D object from 2 vectors. Calls RenderObject::RenderObject(std::vector<GLfloat>* vertexData, std::vector<GLuint>* indexData);
     * \param vertexData Data passed to the GL_ARRAY_BUFFER - vertex coordinates.
     * \param indexData Data passed to the GL_ELEMENT_ARRAY_BUFFER - vertex indices.
     */
    RenderObject2D(std::vector<GLfloat>* vertexData, std::vector<GLuint>* indexData);
    /** \brief Renders the 2D object
     *
     * Must be called on every iteration of the main loop, otherwise the object is not shown/dissappears.
     * \param prg A shader program to use.
     */
    virtual void render(const Program* const prg) const;
};

 #endif // RENDEROBJECT2D_HPP
