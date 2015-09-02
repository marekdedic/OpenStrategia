#include "../include/Slider.hpp"

#include "../include/MultiButton.hpp"
using namespace std;
using namespace glm;

Slider::Slider(int maxState, int initState, glm::vec2 position, glm::vec2 wholeSize, glm::vec2 buttonSize, glm::vec2 sliderSize, std::string texBG, std::string texSlider, std::string texLeftUnpressed, std::string texLeftPressed) : Image(position, wholeSize, texBG), state{initState}, maxState{maxState}, sliderState{false},
leftButton{new MultiButton<Slider>(position, buttonSize, texLeftUnpressed, texLeftPressed, &Slider::decrease, this)},
rightButton{new MultiButton<Slider>(vec2{position.x + wholeSize.x - buttonSize.x, position.y}, buttonSize, texLeftUnpressed, texLeftPressed, &Slider::increase, this)},
slider{new Image{position, sliderSize, texSlider}}
{
    rightButton->texture->vflip();
    rightButton->texture1->vflip();
    if(state > maxState)
    {
        state = maxState / 2;
        ERROR << "initState of slider bigger than maxState. State set to maxState / 2, which is " << state << "." << endl;
    }
    slider->imagePosition = vec2{1.0f * state / maxState * (imageSize.x - 2 * leftButton->imageSize.x - slider->imageSize.x) + imagePosition.x + leftButton->imageSize.x, imagePosition.y};
}

void Slider::handle()
{
    if(slider->click(CURSOR, GLFW_MOUSE_BUTTON_1))
    {
        sliderState = true;
        leftButton->state = 0;
        rightButton->state = 0;
    }
    if((glfwGetMouseButton(WINDOW, GLFW_MOUSE_BUTTON_1) != GLFW_PRESS))
    {
        sliderState = false;
    }
    if(sliderState)
    {
        state = round(maxState * (CURSOR.x - imagePosition.x - leftButton->imageSize.x - 0.5 * slider->imageSize.x) / (imageSize.x - slider->imageSize.x - 2 * leftButton->imageSize.x));
        if(state < 0)
        {
            state = 0;
        }
        if(state > maxState)
        {
            state = maxState;
        }
    }
    else
    {
        leftButton->handle();
        rightButton->handle();
    }
}

void Slider::update()
{
    slider->imagePosition = vec2{1.0f * state / maxState * (imageSize.x - 2 * leftButton->imageSize.x - slider->imageSize.x) + imagePosition.x + leftButton->imageSize.x, imagePosition.y};
    slider->update();
}

void Slider::render(std::shared_ptr<Program> prg) const
{
    Image::render(prg);
    leftButton->render(prg);
    rightButton->render(prg);
    slider->render(prg);
}

void Slider::decrease()
{
    if(state > 0)
    {
        state--;
    }
}

void Slider::increase()
{
    if(state < maxState)
    {
        state++;
    }
}
