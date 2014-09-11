#include "Main.hpp"
using namespace std;
using namespace glm;

Image::Image() :RenderObject2D()
{}

Image::Image(std::vector<GLfloat>* vertexData, std::vector<GLuint>* indexData) : RenderObject2D(vertexData, indexData) {}

void Image::render(const Program* const prg) const
{
    RenderObject2D::render(prg);
}
