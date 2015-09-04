#include "../include/Button.hpp"

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
