#include "../../include/GUI/Checkbox.hpp"

#include "../../include/Texture.hpp"
using namespace std;
using namespace glm;

Checkbox::Checkbox(glm::vec2 inPosition, glm::vec2 inSize, std::string texUnpressed, std::string texPressed) : Image(inPosition, inSize, texUnpressed), state{false}, cooldown(false), texture1{new Texture{texPressed}} {}

void Checkbox::handle()
{
    if(click(CURSOR, GLFW_MOUSE_BUTTON_1))
    {
        if(!cooldown) {state = !state;}
        cooldown = true;
    }
    else
    {
        cooldown = false;
    }
}

void Checkbox::render(std::shared_ptr<Program> prg) const
{
    if(state)
    {
        Image::render(prg, texture1);
    }
    else
    {
        Image::render(prg, texture);
    }
}
