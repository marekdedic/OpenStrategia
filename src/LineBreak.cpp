#include "../Main.hpp"
using namespace std;
using namespace glm;

LineBreak::LineBreak(glm::vec2 inPosition, std::shared_ptr<Font> font, Character* previous) : Character(inPosition, font, 0, previous, 0)
{
    metrics.horiAdvance = 0;
}

void LineBreak::render(std::shared_ptr<Program> prg) const
{
    if(next != nullptr)
    {
        next->render(prg);
    }
}
