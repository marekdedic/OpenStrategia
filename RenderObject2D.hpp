/**
 * \file RenderObject2D.hpp
 * \brief File with RenderObject2D class
 * \author GenaBitu
 **/

#ifndef RENDEROBJECT2D_HPP
#define RENDEROBJECT2D_HPP
#include "Libs.hpp"
#include "RenderObject.hpp"

/** \brief RenderObject2D class
 *
 * This class further develops the functionality of RenderObject to target 2D objects only.
 */
class RenderObject2D : public RenderObject
{
protected:
    /** \brief RenderObject2D class default constructor
     *
     * Initializes all buffers and dynamic variables.
     */
    RenderObject2D();
    /** \brief RenderObject2D constructor
     *
     * Creates an 2D object from 2 vectors. Calls RenderObject::RenderObject(std::vector<GLfloat>* vertexData, std::vector<GLuint>* indexData);
     * \param vertexData Data passed to the GL_ARRAY_BUFFER - vertex coordinates.
     * \param indexData Data passed to the GL_ELEMENT_ARRAY_BUFFER - vertex indices.
     */
     public:
    RenderObject2D(std::shared_ptr<std::vector<GLfloat>> vertexData, std::shared_ptr<std::vector<GLuint>> indexData);
    /** \brief Renders the 2D object
     *
     * Must be called on every iteration of the main loop, otherwise the object is not shown/dissappears.
     * \param prg A shader program to use.
     */
    virtual void render(std::shared_ptr<Program> const prg) const;
};

 #endif // RENDEROBJECT2D_HPP
