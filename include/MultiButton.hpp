/**
 * \file MultiButton.hpp
 * \brief File with MultiButton class
 * \author GenaBitu
 **/

#ifndef MULTIBUTTON_HPP
#define MULTIBUTTON_HPP
#include "Global.hpp"
#include "Button.hpp"

/** \brief MultiButton class
 *
 * The same as the Button class, except when this one is holded, it produces multiple callbacks.
 */
template <class T>
class MultiButton : public Button<T>
{
public:
    MultiButton() = delete;
    /** \brief MultiButton class constructor
     *
     * \param inPosition Position of the MultiButton
     * \param inSize Size of the image represented as vec2(width, height)
     * \param texUnpressed Texture file name for unpressed state
     * \param texPressed Texture file name for pressed state
     * \param func Callback function
     * \param callObject Object on which the func is called
     * \param firstDelay Delay between the first and the second callback
     * \param otherDelay Delay between all other callbacks
     */
    MultiButton(glm::vec2 inPosition, glm::vec2 inSize, std::string texUnpressed, std::string texPressed, void (T::* func)(void), T* callObject, double firstDelay = 0.2, double otherDelay = 0.05);
    /** \brief MultiButton event handle
     *
     * Handles user input.
     */
    virtual void handle() override;
protected:
    double otherDelay; /**< Delay between all callbacks except the after the first one */
};

#include "../src/MultiButton.tpp"

#endif // MULTIBUTTON_HPP
