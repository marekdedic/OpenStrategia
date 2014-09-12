/**
 * \file Button.hpp
 * \brief File with Button class
 * \author GenaBitu
 **/

#ifndef BUTTON_HPP
#define BUTTON_HPP
#include "Libs.hpp"
#include "Image.hpp"

/** \brief Button class
 *
 * This class displays a button in a given location and calls a feedback function when the button is clicked.
 */
class Button : public Image
{
public:
    Button() = delete;
    /** \brief Button class constructor
     *
     * \param Position of the Button.
     * \param Size of the image represented as vec2(width, height).
     * \param Texture file name for unpressed state.
     * \param Texture file name for pressed state.
     * \param Tilting angle.
     */
    Button(glm::vec2 inPosition, glm::vec2 inSize, std::string texUnpressed, std::string texPressed, float angle = 0);
    /** \brief Renders the Button
     *
     * Must be called on every iteration of the main loop, otherwise the object is not shown/dissappears.
     * \param prg A shader program to use.
     */
    virtual void render(std::shared_ptr<Program> prg) const;
protected:
    std::unique_ptr<Texture> texture1; /**< Surface texture of the object. */
    GLint pressed; /**< State of the button. 0 for unpressed, 1 for pressed. */
};

 #endif // BUTTON_HPP
