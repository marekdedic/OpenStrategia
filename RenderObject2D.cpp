#include "Main.hpp"
using namespace std;
using namespace glm;

RenderObject2D::RenderObject2D()
{
     static const GLfloat vertex_buffer_data[] = {
		-0.5f,-1.0f, 0.0f,
		 1.0f,-1.0f, 0.0f,
		 1.0f, 1.0f, 0.0f,
		 0.5f, 1.0f, 0.0f
	};
	static const GLuint element_buffer_data[] = {0,1,3};
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(element_buffer_data), element_buffer_data, GL_STATIC_DRAW);
	indirectData->count = 3;
}

void RenderObject2D::render(const Program* const shaders) const
{
    glDisable(GL_DEPTH_TEST);
    mat4 identity = mat4(1.0f);
    RenderObject::render(shaders, &identity, &identity);
    glEnable(GL_DEPTH_TEST);
}
