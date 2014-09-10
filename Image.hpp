/**
 * \file Image.hpp
 * \brief File with Image class
 * \author GenaBitu
 **/

#ifndef IMAGE_HPP
#define IMAGE_HPP
#include "Libs.hpp"
#include "RenderObject2D.hpp"

/** \brief Image class
 *
 * This class displays a static image in a given location.
 */
class Image : public RenderObject2D
{
    /** \brief Image class default constructor
     *
     * Initializes all buffers and dynamic variables, draws a funky triangle across half the screen.
     */
    Image();
    /** \brief Image constructor
     *
     * Creates an 2D object from 2 vectors. Calls RenderObject2D::RenderObject2D(std::vector<GLfloat>* vertexData, std::vector<GLuint>* indexData);
     * \param vertexData Data passed to the GL_ARRAY_BUFFER - vertex coordinates.
     * \param indexData Data passed to the GL_ELEMENT_ARRAY_BUFFER - vertex indices.
     */
    Image(std::vector<GLfloat>* vertexData, std::vector<GLuint>* indexData);
    /** \brief Renders the Image
     *
     * Must be called on every iteration of the main loop, otherwise the object is not shown/dissappears.
     * \param prg A shader program to use.
     */
    virtual void render(const Program* const prg) const;
};

 #endif // IMAGE_HPP
