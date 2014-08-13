#include "Main.hpp"
using namespace std;
using namespace glm;

Texture::Texture(std::string name) : textureID(0)
{
    name = "textures/" + name;

    unsigned char header[124];

        FILE *fp;

        // try to open the file
        fp = fopen(name.c_str(), "rb");
        if (fp == NULL){
                ERROR << "File could not be opened." << endl;
                glfwSetWindowShouldClose(WINDOW, GL_TRUE);
                return;
        }

        // verify the type of file
        char filecode[4];
        fread(filecode, 1, 4, fp);
        if (strncmp(filecode, "DDS ", 4) != 0) {
                fclose(fp);
                ERROR << "File could not be opened. Not a DDS file." << endl;
                glfwSetWindowShouldClose(WINDOW, GL_TRUE);
                return;
        }

        // get the surface desc
        fread(&header, 124, 1, fp);

        unsigned int height      = *(unsigned int*)&(header[8 ]);
        unsigned int width           = *(unsigned int*)&(header[12]);
        unsigned int linearSize  = *(unsigned int*)&(header[16]);
        unsigned int mipMapCount = *(unsigned int*)&(header[24]);
        unsigned int fourCC      = *(unsigned int*)&(header[80]);


        unsigned char * buffer;
        unsigned int bufsize;
        // how big is it going to be including all mipmaps?
        bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
        buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
        fread(buffer, 1, bufsize, fp);
        // close the file pointer
        fclose(fp);

        unsigned int components  = (fourCC == 0x31545844) ? 3 : 4;
        unsigned int format;
        switch(fourCC)
        {
        case 0x31545844:
                format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
                break;
        case 0x33545844:
                format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
                break;
        case 0x35545844:
                format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
                break;
        default:
                free(buffer);
                ERROR << "File could not be opened. Not a valid DXT compressed file." << endl;
                glfwSetWindowShouldClose(WINDOW, GL_TRUE);
                return;
        }

        // Create one OpenGL texture
        glGenTextures(1, &textureID);

        // "Bind" the newly created texture : all future texture functions will modify this texture
        glBindTexture(GL_TEXTURE_2D, textureID);
        glPixelStorei(GL_UNPACK_ALIGNMENT,1);

        unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
        unsigned int offset = 0;

        // load the mipmaps
        for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
        {
                unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
                glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
                        0, size, buffer + offset);

                offset += size;
                width  /= 2;
                height /= 2;

                // Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
                if(width < 1) width = 1;
                if(height < 1) height = 1;

        }

        free(buffer);
}

Texture::~Texture()
{
    glDeleteTextures(1, &textureID);
}
