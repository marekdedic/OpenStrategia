#include "../include/RenderableComposite.hpp"

RenderableComposite::RenderableComposite() : Renderable{}, children{} {}

void RenderableComposite::add(Renderable* child)
{
    children.push_back(child);
}

void RenderableComposite::rem(std::vector<Renderable*>::const_iterator child)
{
    children.erase(child);
}

RenderableComposite::~RenderableComposite()
{
    children.erase(children.begin(), children.end());
}
