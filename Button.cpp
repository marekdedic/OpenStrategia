#include "Main.hpp"
using namespace std;
using namespace glm;

Button::Button(glm::vec2 inPosition, glm::vec2 inSize, std::string texUnpressed, std::string texPressed, float angle) : Image(inPosition, inSize, texUnpressed, angle), texture1{new Texture{texPressed}}, pressed{0} {}

void Button::render(std::shared_ptr<Program> prg) const
{
    // Send the 1st texture to Graphics card
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture1->textureID);

    Image::render(prg, pressed);
}
