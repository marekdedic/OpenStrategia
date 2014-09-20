#include "Main.hpp"
using namespace std;
using namespace glm;

double Button::pressedTime{0.12};

Button::Button(glm::vec2 inPosition, glm::vec2 inSize, std::string texUnpressed, std::string texPressed, void (*func)(void)) : Image(inPosition, inSize, texUnpressed), texture1{new Texture{texPressed}}, state{0}, callback(func) {}

void Button::handle()
{
    if((state == 0) and (CURSOR.x > imagePosition.x) and (CURSOR.x < (imagePosition.x + imageSize.x)) and (CURSOR.y > imagePosition.y) and (CURSOR.y < (imagePosition.y + imageSize.y)) and (glfwGetMouseButton(WINDOW, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS))
    {
        state = pressedTime;
        callback();
    }
    else if(state > 0)
    {
        if (DELTA > state) {state = -1;}
        else {state -= DELTA;}
    }
    else if((CURSOR.x < imagePosition.x) or (CURSOR.y > (imagePosition.x + imageSize.x)) or (CURSOR.y < imagePosition.y) or (CURSOR.y > (imagePosition.y + imageSize.y)) or (glfwGetMouseButton(WINDOW, GLFW_MOUSE_BUTTON_1) != GLFW_PRESS))
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
