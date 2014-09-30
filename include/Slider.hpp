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
};

 #endif // SLIDER_HPP
