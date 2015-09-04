/**
 * \file RenderObject.hpp
 * \brief File with RenderObject class
 * \author GenaBitu
 **/

#ifndef RENDEROBJECT_HPP
#define RENDEROBJECT_HPP
#include "Global.hpp"
#include "Renderable.hpp"
class Program;

/** \brief RenderObject class
 *
 * This abstract class is used to set and retrieve properties of all objects to be rendered on the screen. Every object to be rendered, 2D or 3D is a child of this class.
 */
class RenderObject : public Renderable
{
protected:
    GLuint VAO; /**< Index of the vertex array object */
    GLuint VBO; /**< Index of the vertex GL_ARRAY_BUFFER */
    GLuint UVBO; /**< Index of the UV coordinates GL_ARRAY_BUFFER */
    GLuint EBO; /**< Index of the GL_ELEMENT_ARRAY_BUFFER */
    /** \brief RenderObject class default constructor
     *
     * Initializes all buffers and dynamic variables.
     */
    RenderObject();
    /** \brief RenderObject class copy constructor
     *
     * Copies all the variables and all the buffers.
     * \param other Address of the RenderObject to copy
     */
    RenderObject(const RenderObject& other);
    /** \brief RenderObject class assignment operator
     *
     * Copies all the variables and all the buffers.
     * \param other Address of the RenderObject to copy
     * \return Address of the new RenderObject
     */
    RenderObject& operator=(const RenderObject& other);
    /** \brief RenderObject constructor
     *
     * Creates an object from 2 vectors.
     * \param vertexData Data passed to the GL_ARRAY_BUFFER - vertex coordinates
     * \param indexData Data passed to the GL_ELEMENT_ARRAY_BUFFER - vertex indices
     */
    RenderObject(std::shared_ptr<std::vector<GLfloat>> vertexData, std::shared_ptr<std::vector<GLuint>> indexData);
    /** \brief Renders the object.
     *
     * Must be called on every iteration of the main loop, otherwise the object is not shown/dissappears.
     * \param prg A shader program to use
     */
    virtual void render(std::shared_ptr<Program> prg) const;
    /** \brief RenderObject class destructor
     *
     * Deletes all dynamically allocated variables and all buffer objects.
     */
    virtual ~RenderObject();
};

 #endif // RENDEROBJECT_HPP
