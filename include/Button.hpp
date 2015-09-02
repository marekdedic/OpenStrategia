/**
 * \file Button.hpp
 * \brief File with Button class
 * \author GenaBitu
 **/

#ifndef BUTTON_HPP
#define BUTTON_HPP
#include "Global.hpp"
#include "Image.hpp"
#include "Texture.hpp"

/** \brief Button class
 *
 * This class displays a button in a given location and calls a feedback function when the button is clicked.
 */
template <class T>
class Button : public Image
{
public:
    std::shared_ptr<Texture> texture1; /**< Surface texture of the Button when it's pressed. */
    double state; /**< State of the button. 0 for unpressed, -1 for pressed but image already changed back, otherwise countdown */
    Button() = delete;
    /** \brief Button class constructor
     *
     * \param inPosition Position of the Button
     * \param inSize Size of the image represented as vec2(width, height)
     * \param texUnpressed Texture file name for unpressed state
     * \param texPressed Texture file name for pressed state
     * \param func Callback function
     * \param callObject Object on which the func is called
     * \param pressedTime Time for which the Button stays visually pressed
     */
    Button(glm::vec2 inPosition, glm::vec2 inSize, std::string texUnpressed, std::string texPressed, void (T::* func)(void), T* callObject, double pressedTime = 0.12);
    /** \brief Button class copy constructor
     *
     * Copies all the pointers.
     * \param other Address of the Button to copy
     */
    Button(const Button& other);
    /** \brief Button class assignment operator
     *
     * Copies all the pointers.
     * \param other Address of the Pointer to copy
     * \return Address of the new Button
     */
    Button& operator=(const Button& other);
    /** \brief Button event handle
     *
     * Handles user input.
     */
    virtual void handle() override;
    /** \brief Renders the Button
     *
     * Must be called on every iteration of the main loop, otherwise the Button is not shown/dissappears.
     * \param prg A shader program to use
     */
    virtual void render(std::shared_ptr<Program> prg) const;
protected:
    double pressedTime; /**< Variable determining for how long should the Button stay visualy pressed */
    void (T::* callback)(void); /**< Button callback function */
    T* const callObject; /**< Button callback object */
};

template<class T>
Button<T>::Button(glm::vec2 inPosition, glm::vec2 inSize, std::string texUnpressed, std::string texPressed, void (T::* func)(void), T* callObject, double pressedTime) : Image(inPosition, inSize, texUnpressed), texture1{new Texture{texPressed}}, state{0}, pressedTime(pressedTime), callback{func}, callObject{callObject} {}

template<class T>
Button<T>::Button(const Button& other) : Image(other), texture1{new Texture{*other.texture1}}, state{0}, pressedTime{other.pressedTime}, callback{other.callback}, callObject{other.callObject} {}

template<class T>
Button<T>& Button<T>::operator=(const Button& other)
{
    Image::operator=(other);
    *texture1 = *other.texture1;
    state = 0;
    pressedTime = other.pressedTime;
    callback = other.callback;
    callObject = other.callObject;
}

template<class T>
void Button<T>::handle()
{
    if((state == 0) and click(CURSOR, GLFW_MOUSE_BUTTON_1))
    {
        state = pressedTime;
        (callObject->*callback)();
    }
    else if(state > 0)
    {
        if (DELTA > state) {state = -1;}
        else {state -= DELTA;}
    }
    if(!click(CURSOR, GLFW_MOUSE_BUTTON_1))
    {
        state = 0;
    }
}

template<class T>
void Button<T>::render(std::shared_ptr<Program> prg) const
{
    if((state == 0) or (state == -1))
    {
        Image::render(prg, texture);
    }
    else
    {
        Image::render(prg, texture1);
    }
}

 #endif // BUTTON_HPP
