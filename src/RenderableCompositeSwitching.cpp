#include "../include/RenderableCompositeSwitching.hpp"
using namespace std;

void RenderableCompositeSwitching::render(std::shared_ptr<Program> prg) const
{
    if(active != children.end())
    {
        (*active)->render(prg);
    }
}

RenderableCompositeSwitching::RenderableCompositeSwitching() : RenderableComposite{}, active{} {}

RenderableCompositeSwitching::~RenderableCompositeSwitching() {}
