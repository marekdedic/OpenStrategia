#include "Main.hpp"
using namespace std;
using namespace glm;

Checkbox::Checkbox(glm::vec2 inPosition, glm::vec2 inSize, std::string texUnpressed, std::string texPressed, float angle) : Image(inPosition, inSize, texUnpressed, angle), state{false}, cooldown(false), texture1{new Texture{texPressed}} {}

void Checkbox::handle()
{
    if((XCURSOR > imagePosition.x) and (XCURSOR < (imagePosition.x + imageSize.x)) and (YCURSOR > imagePosition.y) and (YCURSOR < (imagePosition.y + imageSize.y)) and (glfwGetMouseButton(WINDOW, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS))
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
    // Send the 1st texture to Graphics card
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture1->textureID);

    if(state)
    {
        Image::render(prg, 1);
    }
    else
    {
        Image::render(prg, 0);
    }
}
