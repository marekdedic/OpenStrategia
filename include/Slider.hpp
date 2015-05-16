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
    unsigned int state; /**< State of the Slider ranging from 0 to maxState. */
    const unsigned int maxState; /**< Maximal state of the Slider. */
    Slider() = delete;
    /** \brief Slider class constructor
     *
     * \param inPosition Position of the slider.
     * \param inSize Size of the image represented as vec2(width, height).
     * \param texBG Background Texture file name.
     * \param texLeft Texture file name for left-side button. Right-side button is rendered as a vertical flip of the left one.
     * \param maxState Maximum slider state. Minimum state is 0.
     */
    Slider(unsigned int maxState, unsigned int initState, glm::vec2 position, glm::vec2 wholeSize, glm::vec2 buttonSize, glm::vec2 sliderSize, std::string texBG, std::string texSlider, std::string texLeftUnpressed, std::string texLeftPressed);
    virtual void handle() override;
    /** \brief Update function
     *
     * Must be called on every iteration of the main loop if the Slider is to visualy move.
     */
    virtual void update() override;
    /** \brief Renders the Slider
     *
     * Must be called on every iteration of the main loop, otherwise the object is not shown/dissappears.
     * \param prg A shader program to use.
     */
    virtual void render(std::shared_ptr<Program> prg) const;
protected:
    std::unique_ptr<Button<Slider>> leftButton;
    std::unique_ptr<Button<Slider>> rightButton;
    std::unique_ptr<Image> slider;
    void decrease();
    void increase();
};

 #endif // SLIDER_HPP
