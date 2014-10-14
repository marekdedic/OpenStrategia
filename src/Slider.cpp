#include "../Main.hpp"
using namespace std;
using namespace glm;

Slider::Slider(glm::vec2 inPosition, glm::vec2 inSize, std::string texBG, int maxState, glm::vec2 buttonSize, std::string texLeftPressed, std::string texLeftUnpressed) : Image(inPosition, inSize, texBG), state{}, maxState{maxState}, leftButton{new Button(inPosition, buttonSize, texLeftPressed, texLeftUnpressed, this->decrease1)}
{
}
