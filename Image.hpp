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
    Image() = delete;
    /** \brief Image class constructor
     *
     * \param Position of the Image.
     * \param Size of the image represented as vec2(width, height).
     * \param Texture file name.
     * \param Tilting angle.
     */
    Image(glm::vec2 inPosition, glm::vec2 inSize, std::string tex, float angle = 0);
    /** \brief Renders the Image
     *
     * Must be called on every iteration of the main loop, otherwise the object is not shown/dissappears.
     * \param prg A shader program to use.
     */
    virtual void render(std::shared_ptr<Program> prg, const GLint texUnit = 0) const;
protected:
    glm::vec2 imagePosition;
    glm::vec2 imageSize;
};

 #endif // IMAGE_HPP
