/**
 * \file Checkbox.hpp
 * \brief File with Checkbox class
 * \author GenaBitu
 **/

#ifndef CHECKBOX_HPP
#define CHECKBOX_HPP
#include "Libs.hpp"
#include "Image.hpp"

/** \brief Checkbox class
 *
 * This class displays a checkbox in a given location and offers a boolean state variable.
 */
class Checkbox : public Image
{
public:
    bool state; /**< Checkbox state. */
    Checkbox() = delete;
    /** \brief Checkbox class constructor
     *
     * \param inPosition Position of the Checkbox.
     * \param inSize Size of the image represented as vec2(width, height).
     * \param texUnpressed Texture file name for unpressed state.
     * \param texPressed Texture file name for pressed state.
     */
    Checkbox(glm::vec2 inPosition, glm::vec2 inSize, std::string texUnpressed, std::string texPressed);
    virtual void handle() override;
    /** \brief Renders the Checkbox
     *
     * Must be called on every iteration of the main loop, otherwise the object is not shown/dissappears.
     * \param prg A shader program to use.
     */
    virtual void render(std::shared_ptr<Program> prg) const;
protected:
    bool cooldown;
    std::unique_ptr<Texture> texture1; /**< Surface texture of the object. */
};

 #endif // CHECKBOX_HPP
