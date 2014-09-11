#include "Main.hpp"
using namespace std;
using namespace glm;

Image::Image() :RenderObject2D()
{
    texture.reset(new Texture{"tex2D.bmp"});
    const GLfloat vertex_buffer_data[]{
		 0.0f, 0.0f,
		 1400.0f,0.0f,
		 1400.0f, 1050.0f,
	};
	const GLfloat UV_buffer_data[]{
		 0.0f, 0.0f,
		 1.0f, 0.0f,
		 1.0f, 1.0f,
	};
	const GLuint element_buffer_data[]{0,1,2};
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, UVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(UV_buffer_data), UV_buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(element_buffer_data), element_buffer_data, GL_STATIC_DRAW);
	elementCount = 3;
}

Image::Image(std::vector<GLfloat>* vertexData, std::vector<GLuint>* indexData) : RenderObject2D(vertexData, indexData) {}

void Image::render(const Program* const prg) const
{
    RenderObject2D::render(prg);
}
