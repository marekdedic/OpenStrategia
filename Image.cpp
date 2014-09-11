#include "Main.hpp"
using namespace std;
using namespace glm;

Image::Image(glm::vec2 inPosition, glm::vec2 inSize, float angle, std::string name) : RenderObject2D()
{
    *position = translate(mat4{}, vec3{inPosition, 0});
    *orientation = rotate(mat4{}, angle, vec3{0, 0, 1});
    texture.reset(new Texture{name});
    const GLfloat vertex_buffer_data[]{
		 0, 0,
		 inSize.x, 0,
		 inSize.x, inSize.y,
		 0, inSize.y
	};
	const GLfloat UV_buffer_data[]{
		 0, 0,
		 1, 0,
		 1, 1,
		 0, 1
	};
	const GLuint element_buffer_data[]{0, 1, 2, 0, 2, 3};
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, UVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(UV_buffer_data), UV_buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(element_buffer_data), element_buffer_data, GL_STATIC_DRAW);
	elementCount = 6;
}

Image::Image(std::vector<GLfloat>* vertexData, std::vector<GLuint>* indexData) : RenderObject2D(vertexData, indexData) {}

void Image::render(const Program* const prg) const
{
    RenderObject2D::render(prg);
}
