/**
 * \file Image.hpp
 * \brief File with Image class
 * \author GenaBitu
 **/

#pragma once

#include "../Global.hpp"
#include "../RenderObject2D.hpp"
class Texture;

/** \brief Image class
 *
 * This class displays a static image in a given location.
 */
class Image : public RenderObject2D
{
public:
    glm::vec2 imagePosition; /**< Position of the Image represented as a vec2 */
    glm::vec2 imageSize; /**< Size of the Image represented as a vec2(width, height) */
    float imageAngle;
    std::shared_ptr<Texture> texture; /**< The image itself, as a Texture */
    Image() = delete;
    /** \brief Image class constructor
     *
     * \param inPosition Position of the Image
     * \param inSize Size of the image represented as a vec2(width, height)
     * \param angle Tilting angle in radians
     */
    Image(glm::vec2 inPosition, glm::vec2 inSize, float inAngle = 0);
    /** \brief Image class constructor
     *
     * \param inPosition Position of the Image
     * \param inSize Size of the image represented as a vec2(width, height)
     * \param tex Texture file name
     * \param angle Tilting angle in radians
     */
    Image(glm::vec2 inPosition, glm::vec2 inSize, std::string tex, float inAngle = 0);
    virtual void handle() override;
    /** \brief Update function
     *
     * Must be called on every iteration of the main loop if the Image is to do something.
     */
    virtual void update() override;
    /** \brief Renders the Image with the default Texture
     *
     * Must be called on every iteration of the main loop, otherwise the object is not shown/dissappears.
     * \param prg A shader program to use
     */
    virtual void render(std::shared_ptr<Program> prg) const;
    bool load(std::string tex);
    /** \brief Hover function
     *
     * Returns whether the cursor is over the image, but it does NOT detect pressing of mouse.
     * \param cursor A cursor position to decide for
     * \return True when the cursor is over the Image
     */
    bool hover(glm::dvec2 cursor);
    /** \brief Click function
     *
     * Returns whether the cursor is over the image and the desired mouse button is pressed.
     * \param cursor A cursor position to decide for
     * \param mouseButton A mouse button, which is to be pressed
     * \return True when the cursor is over the image and mouseButton is pressed
     */
    bool click(glm::dvec2 cursor, int mouseButton);
};
