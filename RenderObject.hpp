/**
 * \file RenderObject.hpp
 * \brief File with RenderObject class
 * \author GenaBitu
 **/

#ifndef RENDEROBJECT_HPP
#define RENDEROBJECT_HPP
#include "Libs.hpp"
#include "Texture.hpp"

/** \brief RenderObject class
 *
 * This abstract class is used to set and retrieve properties of all objects to be rendered on the screen. Every object to be rendered, 2D or 3D is a child of this class.
 */
class RenderObject
{
public:
    glm::mat4* position; /**< Position of the RenderObject represented by a matrix */
    glm::mat4* orientation; /**< Orientation of the RenderObject represented by a matrix */
    /** \brief RenderObject class default constructor
     *
     * Initializes all buffers and dynamic variables.
     */
    RenderObject();
    /** \brief RenderObject class copy constructor
     *
     * Copies all the variables and all the buffers.
     * \param other Address of the RenderObject to copy.
     */
    RenderObject(const RenderObject& other);
    /** \brief RenderObject class assignment operator
     *
     * Copies all the variables and all the buffers.
     * \param other Address of the RenderObject to copy.
     * \return Address of the new RenderObject.
     */
    RenderObject& operator=(const RenderObject& other);
    /** \brief RenderObject constructor
     *
     * Creates an object from 2 vectors.
     * \param vertexData Data passed to the GL_ARRAY_BUFFER - vertex coordinates.
     * \param indexData Data passed to the GL_ELEMENT_ARRAY_BUFFER - vertex indices.
     */
    RenderObject(std::vector<GLfloat>* vertexData, std::vector<GLuint>* indexData);
    /** \brief RenderObject event handle
     *
     * Handles user input.
     */
    virtual void handle();
    /** \brief Update function
     *
     * Must be called on every iteration of the main loop if the RenderObject is to do somethink.
     */
    virtual void update();
    /** \brief Renders the object
     *
     * Must be called on every iteration of the main loop, otherwise the object is not shown/dissappears.
     * \param prg A shader program to use.
     * \param viewMatrix A view matrix to use.
     * \param projectionMatrix A projection matrix to use
     */
    virtual void render(const Program* const prg, const glm::mat4* const viewMatrix, const glm::mat4* const projectionMatrix) const;
    /** \brief RenderObject class destructor
     *
     * Deletes all dynamically allocated variables and all buffer objects.
     */
    virtual ~RenderObject();
protected:
    Texture* texture; /**< Surface texture of the object. */
    GLuint VBO; /**< Index of the vertex GL_ARRAY_BUFFER. */
    GLuint UVBO; /**< Index of the UV coordinates GL_ARRAY_BUFFER. */
    GLuint EBO; /**< Index of the GL_ELEMENT_ARRAY_BUFFER. */
    GLuint elementCount; /**< Number of elements single object has. */
};

 #endif // RENDEROBJECT_HPP
