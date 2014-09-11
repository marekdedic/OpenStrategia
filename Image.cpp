#include "Main.hpp"
using namespace std;
using namespace glm;

Image::Image(glm::vec2 inPosition, glm::vec2 inSize, float angle, std::string name) : RenderObject2D()
{
    *position = translate(mat4{}, vec3{inPosition, 0});
    *orientation = rotate(mat4{}, angle, vec3{0, 0, 1});
    texture.reset(new Texture{name});
    vector<GLfloat> vertex_buffer_data{0, 0, inSize.x, 0, inSize.x, inSize.y, 0, inSize.y};
	vector<GLfloat> UV_buffer_data{0, 0, 1, 0, 1, 1, 0, 1};
	vector<GLuint> element_buffer_data{0, 1, 2, 0, 2, 3};
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(GLfloat), vertex_buffer_data.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, UVBO);
	glBufferData(GL_ARRAY_BUFFER, UV_buffer_data.size() * sizeof(GLfloat), UV_buffer_data.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, element_buffer_data.size() * sizeof(GLuint), element_buffer_data.data(), GL_STATIC_DRAW);
}

Image::Image(std::shared_ptr<std::vector<GLfloat>> vertexData, std::shared_ptr<std::vector<GLuint>> indexData) : RenderObject2D(vertexData, indexData) {}

void Image::render(std::shared_ptr<Program> prg) const
{
    RenderObject2D::render(prg);
}
