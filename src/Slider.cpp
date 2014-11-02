#include "../Main.hpp"
using namespace std;
using namespace glm;

Slider::Slider(int maxState, glm::vec2 position, glm::vec2 wholeSize, glm::vec2 buttonSize, glm::vec2 sliderSize, std::string texBG, std::string texSlider, std::string texLeftUnpressed, std::string texLeftPressed) : Image(position, wholeSize, texBG), state{}, maxState{maxState},
leftButton{new Button<Slider>(position, buttonSize, texLeftUnpressed, texLeftPressed, &Slider::decrease, this)},
rightButton{new Button<Slider>(vec2{position.x + wholeSize.x - buttonSize.x, position.y}, buttonSize, texLeftUnpressed, texLeftPressed, &Slider::increase, this)},
slider{new Image{vec2{position.x + 0.5f * wholeSize.x, position.y}, sliderSize, texSlider}} {}

void Slider::handle()
{
    leftButton->handle();
    rightButton->handle();

}

void Slider::render(std::shared_ptr<Program> prg) const
{
    Image::render(prg, 0);
    leftButton->render(prg);
    rightButton->render(prg);
    slider->render(prg, 0);
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
