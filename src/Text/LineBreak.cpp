#include "../../include/LineBreak.hpp"
using namespace std;
using namespace glm;

LineBreak::LineBreak(glm::vec2 inPosition, std::shared_ptr<Font> font, Character* previous) : Character(inPosition, font, 0, previous, 0)
{
    metrics.horiAdvance = 0;
}

void LineBreak::update()
{
    if(previous != nullptr)
    {
        origin.x = 0;
        origin.y = previous->origin.y - (previous->metrics.horiBearingY / 64) - 20;
    }
    imagePosition.x = origin.x;
    imagePosition.y = origin.y;
    if(next != nullptr)
    {
        next->update();
    }
}


void LineBreak::render(std::shared_ptr<Program> prg) const
{
    if(next != nullptr)
    {
        next->render(prg);
    }
}
