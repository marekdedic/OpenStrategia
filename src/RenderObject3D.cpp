#include "../Main.hpp"
using namespace std;
using namespace glm;

RenderObject3D::RenderObject3D() : texture{new Texture{}}, NBO{}                //DEBUG ONLY
{
    glBindVertexArray(VAO);
    glGenBuffers(1, &NBO);

    glBindBuffer(GL_ARRAY_BUFFER, NBO);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    const GLfloat vertex_buffer_data[]{
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
	};
	const GLuint element_buffer_data[]{0,1,2,1,3,2,4,7,5,6,4,5,1,5,7,1,7,3,2,4,0,6,0,4,3,7,4,3,4,2,1,5,6,1,6,0};
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(element_buffer_data), element_buffer_data, GL_STATIC_DRAW);
	glBindVertexArray(0);
}

RenderObject3D::RenderObject3D(const RenderObject3D& other) : RenderObject(other), texture{new Texture{}}, NBO{}
{
    *texture = *other.texture;
    GLint bufferSize{};
    glGenBuffers(1, &NBO);
    glBindBuffer(GL_COPY_READ_BUFFER, other.NBO);
    glGetBufferParameteriv (GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &bufferSize);
    if(bufferSize > 0)
    {
        glBindBuffer(GL_COPY_WRITE_BUFFER, NBO);
        glBufferData(GL_COPY_WRITE_BUFFER, bufferSize, nullptr, GL_STATIC_DRAW);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, bufferSize);
    }
}

RenderObject3D& RenderObject3D::operator=(const RenderObject3D& other)
{
    *texture = *other.texture;
    RenderObject::operator=(other);
    GLint bufferSize{};
    glBindBuffer(GL_COPY_READ_BUFFER, other.NBO);
    glGetBufferParameteriv (GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &bufferSize);
    if(bufferSize > 0)
    {
        glBindBuffer(GL_COPY_WRITE_BUFFER, NBO);
        glBufferData(GL_COPY_WRITE_BUFFER, bufferSize, nullptr, GL_STATIC_DRAW);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, bufferSize);
    }
    return *this;
}

RenderObject3D::RenderObject3D(std::shared_ptr<std::vector<GLfloat>> vertexData, std::shared_ptr<std::vector<GLuint>> indexData) : RenderObject(vertexData, indexData), texture{new Texture{}}, NBO{}
{
    glGenBuffers(1, &NBO);
}

RenderObject3D::RenderObject3D(std::string ObjectName) : RenderObject(), texture{new Texture{}}, NBO{}
{
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glGenBuffers(1, &NBO);
    glBindBuffer(GL_ARRAY_BUFFER, NBO);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    texture->load("tank-tex.bmp");
    ObjectName = "models/" + ObjectName;
    vector<GLuint> vertexIndices{}, UVIndices{}, normalIndices{};
    vector<vec3> rawVertices{};
    vector<vec2> rawUVs{};
    vector<vec3> rawNormals{};
    vector<vec3> vertices{};
    vector<vec2> UVs{};
    vector<vec3> normals{};
    ifstream file{ObjectName};
    string word{};
    vec3 vertex{};
    vec2 coord{};
    GLuint index{};
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
        file.ignore(numeric_limits<streamsize>::max(), '\n');
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
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, UVBO);
    glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(vec2), UVs.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(GLuint), vertexIndices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, NBO);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vec3), normals.data(), GL_STATIC_DRAW);
    glBindVertexArray(0);
}

void RenderObject3D::render(std::shared_ptr<Program> prg, const std::shared_ptr<const Camera> cam) const
{
    // Select shader program
    glUseProgram(prg->ID);

    glBindVertexArray(VAO);

    texture->use(prg, GL_TEXTURE0, 0, "uvMatrix", "oSampler");

    // Compute Model matrix, send it to GLSL
    mat4 modelMatrix{*position * *orientation};
    GLint loc {glGetUniformLocation(prg->ID, "modelMatrix")};
    glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(modelMatrix));

    // Compute ModelViewProjection matrix, send it to GLSL
    mat4 MVP{*cam->projection * *cam->view * modelMatrix};
    loc = glGetUniformLocation(prg->ID, "MVP");
    glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(MVP));

    // Send light position to GLSL
    vec3 LightPosition{-3, 1, 5};
    loc = glGetUniformLocation(prg->ID, "lPosition_w");
    glUniform3fv(loc, 1, value_ptr(LightPosition));

    // Send light falloff distances to GLSL
    float LightFalloffMin{1};
    loc = glGetUniformLocation(prg->ID, "lFalloffMin");
    glUniform1fv(loc, 1, &LightFalloffMin);
    float LightFalloffMax{6};
    loc = glGetUniformLocation(prg->ID, "lFalloffMax");
    glUniform1fv(loc, 1, &LightFalloffMax);

    // Send camera position to GLSL
    loc = glGetUniformLocation(prg->ID, "cPosition_w");
    glUniform3fv(loc, 1, value_ptr(*MAINCAM->position));

    // Render
    RenderObject::render(prg);
    glBindVertexArray(0);
}

RenderObject3D::~RenderObject3D()
{
    glDeleteBuffers(1, &NBO);
}
