#include "Main.hpp"
using namespace std;
using namespace glm;

RenderObject3D::RenderObject3D() : NBO(0), NBOsize(0)        //DEBUG ONLY
{
    glGenBuffers(1, &NBO);
    const GLfloat vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
	};
	const GLuint element_buffer_data[] = {0,1,2,1,3,2,4,7,5,6,4,5,1,5,7,1,7,3,2,4,0,6,0,4,3,7,4,3,4,2,1,5,6,1,6,0};
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(element_buffer_data), element_buffer_data, GL_STATIC_DRAW);
	indirectData->elementCount = 36;
}

RenderObject3D::RenderObject3D(std::vector<GLfloat>* vertexData, std::vector<GLuint>* indexData) : RenderObject(vertexData, indexData), NBO(0), NBOsize(0)
{
    glGenBuffers(1, &NBO);
}

RenderObject3D::RenderObject3D(std::string name) : RenderObject(), NBO(0), NBOsize(0)
{
    glGenBuffers(1, &NBO);
    name = "models/" + name;
    vector<GLuint> vertexIndices, normalIndices;
    vector<vec3> rawVertices;
    vector<vec3> rawNormals;
    vector<vec3> vertices;
    vector<vec3> normals;
    ifstream file(name);
    string word;
    vec3 vertex;
    GLuint index;
    if(!file.is_open())
    {
        ERROR << "Failed to open file: " << name << endl;
        return;
    }
    while(!file.eof())
    {
        file >> word;
        if(word == "vn")
        {
            file >> vertex.x >> vertex.y >> vertex.z;
            rawNormals.push_back(vertex);
            continue;
        }
        if(word == "v")
        {
            file >> vertex.x >> vertex.y >> vertex.z;
            rawVertices.push_back(vertex);
            continue;
        }
        if(word == "f")
        {
            for(unsigned int i = 0; i < 3; i++)
            {
                file >> word;
                index = stoul(word.substr(0, word.find("//")));
                vertexIndices.push_back(index);
                word.erase(0, word.find("//") + 2);
                index = stoul(word);
                normalIndices.push_back(index);
            }
            continue;
        }
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    for(unsigned int i = 0; i < vertexIndices.size(); i++)
    {
        vertex = rawVertices[vertexIndices[i] - 1];
        vertices.push_back(vertex);
        vertex = rawNormals[normalIndices[i] - 1];
        normals.push_back(vertex);
        vertexIndices[i] = i;
        ERROR << vertex.x << " X " << vertex.y << " X " << vertex.z << endl;
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(GLuint), vertexIndices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, NBO);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vec3), normals.data(), GL_STATIC_DRAW);
    indirectData->elementCount = vertexIndices.size();
}

void RenderObject3D::render(const Program* const shaders, const Camera* const cam) const
{
    glBindBuffer(GL_ARRAY_BUFFER, NBO);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    RenderObject::render(shaders, cam->view, cam->projection);
    glDisableVertexAttribArray(1);
}
