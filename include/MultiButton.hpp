/**
 * \file MultiButton.hpp
 * \brief File with MultiButton class
 * \author GenaBitu
 **/

#ifndef MULTIBUTTON_HPP
#define MULTIBUTTON_HPP
#include "Libs.hpp"
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
     * \param inPosition Position of the MultiButton.
     * \param inSize Size of the image represented as vec2(width, height).
     * \param texUnpressed Texture file name for unpressed state.
     * \param texPressed Texture file name for pressed state.
     * \param func Callback function.
     * \param callObject Object on which the func is called.
     * \param firstDelay Delay between the first and the second callback.
     * \param otherDelay Delay between all other callbacks.
     */
    MultiButton(glm::vec2 inPosition, glm::vec2 inSize, std::string texUnpressed, std::string texPressed, void (T::* func)(void), T* callObject, double firstDelay = 0.2, double otherDelay = 0.05);
    virtual void handle() override;
protected:
    double firstDelay;
    double otherDelay;
};

template<class T>
MultiButton<T>::MultiButton(glm::vec2 inPosition, glm::vec2 inSize, std::string texUnpressed, std::string texPressed, void (T::* func)(void), T* callObject, double firstDelay, double otherDelay) : Button<T>(inPosition, inSize, texUnpressed, texPressed, func, callObject, firstDelay), firstDelay{firstDelay}, otherDelay{otherDelay} {}

template<class T>
void MultiButton<T>::handle()
{
    if(Button<T>::state == -1)
    {
        Button<T>::state = otherDelay;
        (Button<T>::callObject->*Button<T>::callback)();
    }
    Button<T>::handle();
}

#endif // MULTIBUTTON_HPP
