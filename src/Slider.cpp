#include "../Main.hpp"
using namespace std;
using namespace glm;

Slider::Slider(unsigned int maxState, unsigned int initState, glm::vec2 position, glm::vec2 wholeSize, glm::vec2 buttonSize, glm::vec2 sliderSize, std::string texBG, std::string texSlider, std::string texLeftUnpressed, std::string texLeftPressed) : Image(position, wholeSize, texBG), state{initState}, maxState{maxState},
leftButton{new MultiButton<Slider>(position, buttonSize, texLeftUnpressed, texLeftPressed, &Slider::decrease, this)},
rightButton{new MultiButton<Slider>(vec2{position.x + wholeSize.x - buttonSize.x, position.y}, buttonSize, texLeftUnpressed, texLeftPressed, &Slider::increase, this)},
slider{new Image{position, sliderSize, texSlider}}
{
    if(state > maxState)
    {
        state = maxState / 2;
        ERROR << "initState of slider bigger than maxState. State set to maxState / 2, which is " << state << "." << endl;
    }
    slider->imagePosition = vec2{1.0f * state / maxState * (imageSize.x - 2 * leftButton->imageSize.x - slider->imageSize.x) + imagePosition.x + leftButton->imageSize.x, imagePosition.y};
}

void Slider::handle()
{
    leftButton->handle();
    rightButton->handle();
}

void Slider::update()
{
    slider->imagePosition = vec2{1.0f * state / maxState * (imageSize.x - 2 * leftButton->imageSize.x - slider->imageSize.x) + imagePosition.x + leftButton->imageSize.x, imagePosition.y};
    slider->update();
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
