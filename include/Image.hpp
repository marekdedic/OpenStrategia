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
public:
    glm::vec2 imagePosition; /**< Position of the Image represented as a vec2. */
    glm::vec2 imageSize; /**< Size of the Image represented as a vec2(width, height). */
    Image() = delete;
    /** \brief Image class constructor
     *
     * \param inPosition Position of the Image.
     * \param inSize Size of the image represented as a vec2(width, height).
     * \param tex Texture file name.
     * \param angle Tilting angle.
     */
    Image(glm::vec2 inPosition, glm::vec2 inSize, std::string tex, float angle = 0);
    /** \brief Update function
     *
     * Must be called on every iteration of the main loop if the Image is to do somethink.
     */
    virtual void update();
    /** \brief Renders the Image
     *
     * Must be called on every iteration of the main loop, otherwise the object is not shown/dissappears.
     * \param prg A shader program to use.
     * \param texUnit The number of the texture unit to use
     */
    virtual void render(std::shared_ptr<Program> prg, const GLint texUnit = 0) const;
};

 #endif // IMAGE_HPP
