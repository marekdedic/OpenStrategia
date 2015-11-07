/**
 * \file Checkbox.hpp
 * \brief File with Checkbox class
 * \author GenaBitu
 **/

#ifndef CHECKBOX_HPP
#define CHECKBOX_HPP
#include "../Global.hpp"
#include "../RenderableCompositeSwitching.hpp"
#include "Image.hpp"

/** \brief Checkbox class
 *
 * This class displays a checkbox in a given location and offers a boolean state variable.
 */
class Checkbox : public RenderableCompositeSwitching
{
public:
    bool state; /**< Checkbox state true=pressed */
    /** \brief Checkbox class constructor
     *
     * \param inPosition Position of the Checkbox
     * \param inSize Size of the image represented as vec2(width, height)
     * \param texUnpressed Texture file name for unpressed state
     * \param texPressed Texture file name for pressed state
     */
    Checkbox(glm::vec2 inPosition, glm::vec2 inSize, std::string texUnpressed, std::string texPressed);
    /** \brief Checkbox event handle
     *
     * Handles user input.
     */
    virtual void handle() override;
    virtual void update() override;
protected:
    bool cooldown; /**< True when the Checkbox has been pressed but the mouse is still pressing it. Avoids multiple presses. */
    glm::vec2 imagePosition; /**< Position of the Image represented as a vec2 */
    glm::vec2 imageSize; /**< Size of the Image represented as a vec2(width, height) */
    bool hover(glm::dvec2 cursor);
    bool click(glm::dvec2 cursor, int mouseButton);
};

 #endif // CHECKBOX_HPP
