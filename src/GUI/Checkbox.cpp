#include "../../include/GUI/Checkbox.hpp"

#include "../../include/Texture.hpp"
using namespace std;
using namespace glm;

Checkbox::Checkbox(glm::vec2 inPosition, glm::vec2 inSize, std::string texUnpressed, std::string texPressed) : RenderableCompositeSwitching{}, state{false}, cooldown(false)
{
    add(new Image{inPosition, inSize, texUnpressed});
    add(new Image{inPosition, inSize, texPressed});
}

void Checkbox::handle()
{
    /*if(dynamic_cast<Image*>(*(children.begin()))->click(CURSOR, GLFW_MOUSE_BUTTON_1))
    {
        if(!cooldown) {state = !state;}
        cooldown = true;
    }
    else
    {
        cooldown = false;
    }*/
}

void Checkbox::update()
{
    if(state)
    {
        active = 1;
    }
    else
    {
        active = 0;
    }
}
