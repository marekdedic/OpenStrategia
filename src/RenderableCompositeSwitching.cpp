#include "../include/RenderableCompositeSwitching.hpp"
using namespace std;

void RenderableCompositeSwitching::render(std::shared_ptr<Program> prg) const
{
    if(active >= 0)
    {
        children[active]->render(prg);
    }
}

RenderableCompositeSwitching::RenderableCompositeSwitching() : RenderableComposite{}, active{-1} {}

RenderableCompositeSwitching::~RenderableCompositeSwitching() {}
