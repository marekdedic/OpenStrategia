#include "../../include/GUI/MultiButton.hpp"

template<class T>
MultiButton<T>::MultiButton(glm::vec2 inPosition, glm::vec2 inSize, std::string texUnpressed, std::string texPressed, void (T::* func)(void), T* callObject, double firstDelay, double otherDelay) : Button<T>(inPosition, inSize, texUnpressed, texPressed, func, callObject, firstDelay), otherDelay{otherDelay} {}

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
