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
    static double pressedTime; /**< Static variable determining for how long should the Button stay visualy pressed. */
    Button() = delete;
    /** \brief Button class constructor
     *
     * \param inPosition Position of the Button.
     * \param inSize Size of the image represented as vec2(width, height).
     * \param texUnpressed Texture file name for unpressed state.
     * \param texPressed Texture file name for pressed state.
     * \param func Callback function
     * \param angle Tilting angle.
     */
    Button(glm::vec2 inPosition, glm::vec2 inSize, std::string texUnpressed, std::string texPressed, void (*func)(void),  float angle = 0);
    virtual void handle();
    /** \brief Renders the Button
     *
     * Must be called on every iteration of the main loop, otherwise the object is not shown/dissappears.
     * \param prg A shader program to use.
     */
    virtual void render(std::shared_ptr<Program> prg) const;
protected:
    std::unique_ptr<Texture> texture1; /**< Surface texture of the object. */
    double state; /**< State of the button. 0 for unpressed, -1 for pressed but image already changed back, otherwise countdown. */
    void (*callback)(void); /**< Button callback function. */
};

 #endif // BUTTON_HPP
