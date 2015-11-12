#include "../include/RenderableCompositeSwitching.hpp"
using namespace std;

void RenderableCompositeSwitching::render(std::shared_ptr<Program> prg) const
{
    if(active >= 0)
    {
        children[active]->render(prg);
    }
}

RenderableCompositeSwitching::RenderableCompositeSwitching(std::shared_ptr<glm::mat4> position, std::shared_ptr<glm::mat4> orientation) : RenderableComposite{position, orientation}, active{-1} {}

RenderableCompositeSwitching::~RenderableCompositeSwitching() {}
