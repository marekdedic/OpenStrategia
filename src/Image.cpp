#include "../Main.hpp"
using namespace std;
using namespace glm;

Image::Image(glm::vec2 inPosition, glm::vec2 inSize, std::string name, float angle) : RenderObject2D(), imagePosition{inPosition}, imageSize{inSize}
{
    *position = translate(mat4{}, vec3{imagePosition, 0});
    *orientation = rotate(mat4{}, angle, vec3{0, 0, 1});
    texture->load(name);
    vector<GLfloat> vertex_buffer_data{0, 0, imageSize.x, 0, imageSize.x, imageSize.y, 0, imageSize.y};
	vector<GLfloat> UV_buffer_data{0, 0, 1, 0, 1, 1, 0, 1};
	vector<GLuint> element_buffer_data{0, 1, 2, 0, 2, 3};
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(GLfloat), vertex_buffer_data.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, UVBO);
	glBufferData(GL_ARRAY_BUFFER, UV_buffer_data.size() * sizeof(GLfloat), UV_buffer_data.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, element_buffer_data.size() * sizeof(GLuint), element_buffer_data.data(), GL_STATIC_DRAW);
}

void Image::update()
{
    *position = translate(mat4{}, vec3{imagePosition, 0});
}

void Image::render(std::shared_ptr<Program> prg, const GLint texUnit) const
{
    *position = translate(mat4{}, vec3{imagePosition, 0});
    RenderObject2D::render(prg, texUnit);
}
