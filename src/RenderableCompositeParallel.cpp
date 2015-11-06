#include "../include/RenderableCompositeParallel.hpp"
using namespace std;

void RenderableCompositeParallel::render(std::shared_ptr<Program> prg) const
{
    for(vector<Renderable*>::const_iterator it(children.begin()); it < children.end(); it++)
    {
        (*it)->render(prg);
    }
}

RenderableCompositeParallel::RenderableCompositeParallel() : RenderableComposite{} {}

RenderableCompositeParallel::~RenderableCompositeParallel() {}
