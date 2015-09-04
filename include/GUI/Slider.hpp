/**
 * \file Slider.hpp
 * \brief File with Slider class
 * \author GenaBitu
 **/

#ifndef SLIDER_HPP
#define SLIDER_HPP
#include "../Global.hpp"
#include "Image.hpp"
template <class T> class MultiButton;

/** \brief Slider class
 *
 * This class displays a slider in a given location and offers a value variable.
 */
class Slider : public Image
{
public:
    int state; /**< State of the Slider ranging from 0 to maxState */
    Slider() = delete;
    /** \brief Slider class constructor
     *
     * \param maxState Maximum slider state. Minimum state is 0.
     * \param initState Slider state upon creation. If bigger than maxState, it's set to floor(maxState/2) and an error is written to the log.
     * \param position Position of the slider
     * \param wholeSize Size of the whole Slider represented as vec2(width, height)
     * \param buttonSize Size of the left button represented as vec2(width, height). Right button will have the same size.
     * \param sliderSize Size of the actual sliding part represented as vec2(width, height)
     * \param texBG Background Texture file name
     * \param texSlider Texture file name for the sliding part
     * \param texLeftUnpressed Texture file name for left-side button when unpressed. Right-side button is rendered as a vertical flip of the left one.
     * \param texLeftPressed Texture file name for left-side button when pressed. Right-side button is rendered as a vertical flip of the left one.
     */
    Slider(int maxState, int initState, glm::vec2 position, glm::vec2 wholeSize, glm::vec2 buttonSize, glm::vec2 sliderSize, std::string texBG, std::string texSlider, std::string texLeftUnpressed, std::string texLeftPressed);
    /** \brief Slider event handle
     *
     * Handles user input.
     */
    virtual void handle() override;
    /** \brief Update function
     *
     * Must be called on every iteration of the main loop if the Slider is to visualy move.
     */
    virtual void update() override;
    /** \brief Renders the Slider
     *
     * Must be called on every iteration of the main loop, otherwise the Slider is not shown/dissappears.
     * \param prg A shader program to use.
     */
    virtual void render(std::shared_ptr<Program> prg) const;
protected:
    const int maxState; /**< Maximum state of the Slider */
    bool sliderState; /**< True when the sliding part was pressed and not released yet, even if the mouse has gone outside its boundaries. */
    std::unique_ptr<MultiButton<Slider>> leftButton; /**< Decrease button */
    std::unique_ptr<MultiButton<Slider>> rightButton; /**< Increase button */
    std::unique_ptr<Image> slider; /**< The sliding part */
    void decrease(); /**< Decrease function callback */
    void increase(); /**< Increase function callback */
};

 #endif // SLIDER_HPP
