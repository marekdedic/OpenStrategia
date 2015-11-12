#include "../../include/GUI/Checkbox.hpp"
using namespace std;
using namespace glm;

Checkbox::Checkbox(glm::vec2 inPosition, glm::vec2 inSize, std::string texUnpressed, std::string texPressed) : RenderableCompositeSwitching(shared_ptr<mat4>{new mat4{translate(mat4{}, vec3{imagePosition, 0})}}, shared_ptr<mat4>{new mat4{}}), state{false}, cooldown(false), imagePosition{inPosition}, imageSize{inSize}
{
    add(new Image{inPosition, inSize, texUnpressed});
    add(new Image{inPosition, inSize, texPressed});
}

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

bool Checkbox::hover(glm::dvec2 cursor)
{
    dvec4 transformedCursor{cursor.x, cursor.y, 0, 0};
    transformedCursor -= dvec4{imagePosition.x, imagePosition.y, 0, 0};
    transformedCursor = dmat4{inverse(*orientation)} * transformedCursor;
    return ((transformedCursor.x > 0) and (transformedCursor.x < imageSize.x) and (transformedCursor.y > 0) and (transformedCursor.y < imageSize.y));
}

bool Checkbox::click(glm::dvec2 cursor, int mouseButton)
{
    return (hover(cursor) and (glfwGetMouseButton(WINDOW, mouseButton) == GLFW_PRESS));
}
