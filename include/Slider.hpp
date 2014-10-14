/**
 * \file Slider.hpp
 * \brief File with Slider class
 * \author GenaBitu
 **/

#ifndef SLIDER_HPP
#define SLIDER_HPP
#include "Libs.hpp"
#include "Image.hpp"
#include "Button.hpp"

/** \brief Slider class
 *
 * This class displays a slider in a given location and offers a value variable.
 */
class Slider : public Image
{
public:
    int state; /**< State of the Slider ranging from 0 to maxState. */
    const int maxState; /**< Maximal state of the Slider. */
    Slider() = delete;
    /** \brief Slider class constructor
     *
     * \param inPosition Position of the slider.
     * \param inSize Size of the image represented as vec2(width, height).
     * \param texBG Background Texture file name.
     * \param texLeft Texture file name for left-side button. Right-side button is rendered as a vertical flip of the left one.
     * \param maxState Maximum slider state. Minimum state is 0.
     */
    Slider(glm::vec2 inPosition, glm::vec2 inSize, std::string texBG, int maxState, glm::vec2 buttonSize, std::string texLeftPressed, std::string texLeftUnpressed);
    virtual void handle();
    /** \brief Renders the Slider
     *
     * Must be called on every iteration of the main loop, otherwise the object is not shown/dissappears.
     * \param prg A shader program to use.
     */
    virtual void render(std::shared_ptr<Program> prg) const;
protected:
    std::unique_ptr<Button> leftButton;
    std::unique_ptr<Button> rightButton;
    void decrease1();
    void increase();
};

 #endif // SLIDER_HPP
