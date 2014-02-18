/**
 * \file RenderObject3D.hpp
 * \brief File with RenderObject3D class
 * \author GenaBitu
 **/

#ifndef RENDEROBJECT3D_HPP
#define RENDEROBJECT3D_HPP
#include "Libs.hpp"

/** \brief RenderObject3D class
 *
 * This class further develops the functionality of RenderObject to target 3D objects only.
 */
class RenderObject3D : public RenderObject
{
public:
    /** \brief RenderObject3D class default constructor
     *
     * Initializes all buffers and dynamic variables, draws a funky cube.
     */
    RenderObject3D();
    /** \brief RenderObject3D constructor
     *
     * Creates an object from 2 vectors.
     * \param vertexData Data passed to the GL_ARRAY_BUFFER - vertex coordinates.
     * \param indexData Data passed to the GL_ELEMENT_ARRAY_BUFFER - vertex indices.
     */
    RenderObject3D(std::vector<GLfloat>* vertexData, std::vector<GLuint>* indexData);
    /** \brief RenderObject3D constructor
     *
     * Creates an object from a .OBJ file.
     * \param name Filename with extension, relative to the models subdir.
     */
    RenderObject3D(std::string name);
    /** \brief Renders the 3D object
     *
     * Must be called on every iteration of the main loop, otherwise the object is not shown/dissappears.
     * \param prg A shader program to use.
     * \param cam A Camera to render the object with.
     */
    virtual void render(const Program* const prg, const Camera* const cam) const;
protected:
    GLuint NBO; /**< Index of the GL_ARRAY_BUFFER containing normals. */
    GLsizei NBOsize; /**< Size of the GL_ARRAY_BUFFER containing normals. */
};

 #endif // RENDEROBJECT3D_HPP
