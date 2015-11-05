#include "../include/RenderableCompositeParallel.hpp"
using namespace std;

void RenderableCompositeParallel::update()
{
    for(vector<Renderable*>::iterator it{children.begin()}; it < children.end(); it++)
    {
        (*it)->update();
    }
}

RenderableCompositeParallel::RenderableCompositeParallel() : RenderableComposite{} {}

RenderableCompositeParallel::~RenderableCompositeParallel() {}
