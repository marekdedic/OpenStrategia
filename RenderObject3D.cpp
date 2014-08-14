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
	VBOsize = sizeof(vertex_buffer_data);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, VBOsize, vertex_buffer_data, GL_STATIC_DRAW);
	EBOsize = sizeof(element_buffer_data);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, EBOsize, element_buffer_data, GL_STATIC_DRAW);
	indirectData->elementCount = 36;
}

RenderObject3D::RenderObject3D(const RenderObject3D& other) : RenderObject(other), NBO(0), NBOsize(other.NBOsize)
{
    ERROR << "called" << endl;
    glGenBuffers(1, &NBO);
    glBindBuffer(GL_COPY_READ_BUFFER, NBO);
    glBindBuffer(GL_COPY_WRITE_BUFFER, other.NBO);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, NBOsize);
}

/*RenderObject& RenderObject::operator=(const RenderObject& other)
{
    if(this != &other)
    {
        position = other.position;
        orientation = other.orientation;
        texture = other.texture;
        VBO = 0;
        VBOsize = other.VBOsize;
        UVBO = 0;
        UVBOsize = other.UVBOsize;
        EBO = 0;
        EBOsize = other.EBOsize;
        IBO = 0;
        IBOsize = other.IBOsize;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_COPY_READ_BUFFER, VBO);
        glBindBuffer(GL_COPY_WRITE_BUFFER, other.VBO);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, VBOsize);
        glGenBuffers(1, &UVBO);
        glBindBuffer(GL_COPY_READ_BUFFER, UVBO);
        glBindBuffer(GL_COPY_WRITE_BUFFER, other.UVBO);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, UVBOsize);
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_COPY_READ_BUFFER, EBO);
        glBindBuffer(GL_COPY_WRITE_BUFFER, other.EBO);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, EBOsize);
        glGenBuffers(1, &IBO);
        glBindBuffer(GL_COPY_READ_BUFFER, IBO);
        glBindBuffer(GL_COPY_WRITE_BUFFER, other.IBO);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, IBOsize);
        indirectData = new DrawElementsIndirectCommand;
        *indirectData = *(other.indirectData);
    }
    return *this;
}*/

RenderObject3D::RenderObject3D(std::vector<GLfloat>* vertexData, std::vector<GLuint>* indexData) : RenderObject(vertexData, indexData), NBO(0), NBOsize(0)
{
    glGenBuffers(1, &NBO);
}

RenderObject3D::RenderObject3D(std::string ObjectName) : RenderObject(), NBO(0), NBOsize(0)
{
    glGenBuffers(1, &NBO);
    ObjectName = "models/" + ObjectName;
    vector<GLuint> vertexIndices, UVIndices, normalIndices;
    vector<vec3> rawVertices;
    vector<vec2> rawUVs;
    vector<vec3> rawNormals;
    vector<vec3> vertices;
    vector<vec2> UVs;
    vector<vec3> normals;
    ifstream file(ObjectName);
    string word;
    vec3 vertex;
    vec2 coord;
    GLuint index;
    if(!file.is_open())
    {
        ERROR << "Failed to open file: " << ObjectName << endl;
        return;
    }
    while(!file.eof())
    {
        file >> word;
        if(word == "vt")
        {
            file >> coord.x >> coord.y;
            rawUVs.push_back(coord);
            continue;
        }
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
                index = stoul(word.substr(0, word.find("/")));
                vertexIndices.push_back(index);
                word.erase(0, word.find("/") + 1);
                index = stoul(word.substr(0, word.find("/")));
                UVIndices.push_back(index);
                word.erase(0, word.find("/") + 1);
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
        coord = rawUVs[UVIndices[i] - 1];
        UVs.push_back(coord);
        vertex = rawNormals[normalIndices[i] - 1];
        normals.push_back(vertex);
        vertexIndices[i] = i;
    }
    VBOsize = vertices.size() * sizeof(vec3);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, VBOsize, vertices.data(), GL_STATIC_DRAW);
    UVBOsize = UVs.size() * sizeof(vec2);
    glBindBuffer(GL_ARRAY_BUFFER, UVBO);
    glBufferData(GL_ARRAY_BUFFER, UVBOsize, UVs.data(), GL_STATIC_DRAW);
    EBOsize = vertexIndices.size() * sizeof(GLuint);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, EBOsize, vertexIndices.data(), GL_STATIC_DRAW);
    NBOsize = normals.size() * sizeof(vec3);
    glBindBuffer(GL_ARRAY_BUFFER, NBO);
    glBufferData(GL_ARRAY_BUFFER, NBOsize, normals.data(), GL_STATIC_DRAW);
    indirectData->elementCount = vertexIndices.size();
}

void RenderObject3D::render(const Program* const shaders, const Camera* const cam) const
{
    glBindBuffer(GL_ARRAY_BUFFER, NBO);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    RenderObject::render(shaders, cam->view, cam->projection);
    glDisableVertexAttribArray(2);
}

RenderObject3D::~RenderObject3D()
{
    glDeleteBuffers(1, &NBO);
}
