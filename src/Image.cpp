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

void Image::render(std::shared_ptr<Program> prg, const GLint texUnit) const
{
    // Send the 0th texture to Graphics card
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->ID);

    // Send the Texture transformation matrix to GLSL
    GLint loc{glGetUniformLocation(prg->ID, "uvMatrix")};
    glUniformMatrix3fv(loc, 1, GL_FALSE, value_ptr(texture->transformation));

    // Use texture unit 0
    loc = glGetUniformLocation(prg->ID, "oSampler");
    glUniform1i(loc, texUnit);
    RenderObject2D::render(prg, texUnit);
}

bool Image::hover(glm::dvec2 cursor)
{
    return ((cursor.x > imagePosition.x) and (cursor.x < (imagePosition.x + imageSize.x)) and (cursor.y > imagePosition.y) and (cursor.y < (imagePosition.y + imageSize.y)));
}

bool Image::click(glm::dvec2 cursor, int mouseButton)
{
    return (hover(cursor) and (glfwGetMouseButton(WINDOW, mouseButton) == GLFW_PRESS));
}
