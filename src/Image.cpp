#include "../Main.hpp"
using namespace std;
using namespace glm;

Image::Image(glm::vec2 inPosition, glm::vec2 inSize, std::string name, float angle) : RenderObject2D(), imagePosition{inPosition}, imageSize{inSize}, texture{new Texture{}}
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

void Image::render(std::shared_ptr<Program> prg) const
{
    render(prg, texture);
}

void Image::render(std::shared_ptr<Program> prg, std::shared_ptr<Texture> activeTexture) const
{
    glUseProgram(prg->ID);

    activeTexture->use(prg, GL_TEXTURE0, 0, "uvMatrix", "oSampler");
    RenderObject2D::render(prg);
}

bool Image::hover(glm::dvec2 cursor)
{
    dvec4 transformedCursor{cursor.x, cursor.y, 0, 0};
    transformedCursor -= fvec4{imagePosition.x, imagePosition.y, 0, 0};
    transformedCursor = inverse(dmat4{*orientation}) * transformedCursor;
    return ((transformedCursor.x > 0) and (transformedCursor.x < imageSize.x) and (transformedCursor.y > 0) and (transformedCursor.y < imageSize.y));
}

bool Image::click(glm::dvec2 cursor, int mouseButton)
{
    return (hover(cursor) and (glfwGetMouseButton(WINDOW, mouseButton) == GLFW_PRESS));
}
