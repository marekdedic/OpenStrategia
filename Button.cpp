#include "Main.hpp"
using namespace std;
using namespace glm;

double Button::pressedTime{0.12};

Button::Button(glm::vec2 inPosition, glm::vec2 inSize, std::string texUnpressed, std::string texPressed, float angle) : Image(inPosition, inSize, texUnpressed, angle), texture1{new Texture{texPressed}}, state{0} {}

void Button::handle()
{
    if((state == 0) and (XCURSOR > imagePosition.x) and (XCURSOR < (imagePosition.x + imageSize.x)) and (YCURSOR > imagePosition.y) and (YCURSOR < (imagePosition.y + imageSize.y)) and (glfwGetMouseButton(WINDOW, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS))
    {
        state = pressedTime;
    }
    else if(state > 0)
    {
        ERROR << state << endl;
        if (DELTA > state) {state = -1;}
        else {state -= DELTA;}
    }
    else if((XCURSOR < imagePosition.x) or (XCURSOR > (imagePosition.x + imageSize.x)) or (YCURSOR < imagePosition.y) or (YCURSOR > (imagePosition.y + imageSize.y)) or (glfwGetMouseButton(WINDOW, GLFW_MOUSE_BUTTON_1) != GLFW_PRESS))
    {
        state = 0;
    }
}

void Button::render(std::shared_ptr<Program> prg) const
{
    // Send the 1st texture to Graphics card
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture1->textureID);

    if((state == 0) or (state == -1))
    {
        Image::render(prg, 0);
    }
    else
    {
        Image::render(prg, 1);
    }
}
