/**
 * \file Button.hpp
 * \brief File with Button class
 * \author GenaBitu
 **/

#ifndef BUTTON_HPP
#define BUTTON_HPP
#include "Libs.hpp"
#include "Image.hpp"

extern glm::dvec2 CURSOR;
extern GLFWwindow* WINDOW;
extern double DELTA;

/** \brief Button class
 *
 * This class displays a button in a given location and calls a feedback function when the button is clicked.
 */
template <class T>
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
     */
    Button(glm::vec2 inPosition, glm::vec2 inSize, std::string texUnpressed, std::string texPressed, void (T::* func)(void), T* callObject);
    /** \brief Button class copy constructor
     *
     * Copies all the pointers.
     * \param other Address of the Button to copy.
     */
    Button(const Button& other);
    /** \brief Button class assignment operator
     *
     * Copies all the pointers.
     * \param other Address of the Pointer to copy.
     * \return Address of the new Button.
     */
    Button& operator=(const Button& other);
    virtual void handle() override;
    /** \brief Renders the Button
     *
     * Must be called on every iteration of the main loop, otherwise the object is not shown/dissappears.
     * \param prg A shader program to use.
     */
    virtual void render(std::shared_ptr<Program> prg) const;
protected:
    std::unique_ptr<Texture> texture1; /**< Surface texture of the object. */
    double state; /**< State of the button. 0 for unpressed, -1 for pressed but image already changed back, otherwise countdown. */
    void (T::* callback)(void); /**< Button callback function. */
    T* const callObject; /**< Button callback object. */
};

template<class T>
double Button<T>::pressedTime{0.12};

template<class T>
Button<T>::Button(glm::vec2 inPosition, glm::vec2 inSize, std::string texUnpressed, std::string texPressed, void (T::* func)(void), T* callObject) : Image(inPosition, inSize, texUnpressed), texture1{new Texture{texPressed}}, state{0}, callback{func}, callObject{callObject} {}

template<class T>
Button<T>::Button(const Button& other) : Image(other), texture1{new Texture{*other.texture1}}, state{0}, callback{other.callback}, callObject{other.callObject} {}

template<class T>
Button<T>& Button<T>::operator=(const Button& other)
{
    Image::operator=(other);
    *texture1 = *other.texture1;
    state = 0;
    callback = other.callback;
    callObject = other.callObject;
}

template<class T>
void Button<T>::handle()
{
    if((state == 0) and (CURSOR.x > imagePosition.x) and (CURSOR.x < (imagePosition.x + imageSize.x)) and (CURSOR.y > imagePosition.y) and (CURSOR.y < (imagePosition.y + imageSize.y)) and (glfwGetMouseButton(WINDOW, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS))
    {
        state = pressedTime;
        (callObject->*callback)();
    }
    else if(state > 0)
    {
        if (DELTA > state) {state = -1;}
        else {state -= DELTA;}
    }
    else if((CURSOR.x < imagePosition.x) or (CURSOR.y > (imagePosition.x + imageSize.x)) or (CURSOR.y < imagePosition.y) or (CURSOR.y > (imagePosition.y + imageSize.y)) or (glfwGetMouseButton(WINDOW, GLFW_MOUSE_BUTTON_1) != GLFW_PRESS))
    {
        state = 0;
    }
}

template<class T>
void Button<T>::render(std::shared_ptr<Program> prg) const
{
    // Send the 1st texture to Graphics card
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture1->ID);

    if((state == 0) or (state == -1))
    {
        Image::render(prg, 0);
    }
    else
    {
        Image::render(prg, 1);
    }
}

 #endif // BUTTON_HPP
