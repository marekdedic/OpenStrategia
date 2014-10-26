#include "../Main.hpp"
using namespace std;
using namespace glm;

Slider::Slider(glm::vec2 inPosition, glm::vec2 inSize, std::string texBG, int maxState, glm::vec2 buttonSize, std::string texLeftPressed, std::string texLeftUnpressed) : Image(inPosition, inSize, texBG), state{}, maxState{maxState},
leftButton{new Button<Slider>(inPosition, buttonSize, texLeftPressed, texLeftUnpressed, &Slider::decrease, this)},
rightButton{new Button<Slider>(inPosition + inSize - buttonSize, buttonSize, texLeftPressed, texLeftUnpressed, &Slider::increase, this)}
{
}

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
