#include "Main.hpp"
using namespace std;
using namespace glm;

Camera* RenderObject2D::cam2D = new Camera(0, 4.0 / 3.0, 0, vec3(0, 0, 0), quat(0, 0, 0, 0));
//mat4* RenderObject2D::cam2D->view = mat4(1);                 //UBER_HACK
//*cam2D->projection = mat4(1);

RenderObject2D::RenderObject2D()
{
     static const GLfloat vertex_buffer_data[] = {
		-1.0f,-1.0f, 0.0f,
		 1.0f,-1.0f, 0.0f,
		 1.0f, 1.0f, 0.0f,
	};
	static const GLuint element_buffer_data[] = {0,1,2};
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(element_buffer_data), element_buffer_data, GL_STATIC_DRAW);
	EBOsize = 3;
}

void RenderObject2D::render(const Program* const shaders) const
{
    glDisable(GL_DEPTH_TEST);
    RenderObject::render(shaders, cam2D);
    glEnable(GL_DEPTH_TEST);
}
