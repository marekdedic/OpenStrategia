/**
 * @file Shader.hpp
 * File with Shader class
 * @author GenaBitu
 **/

#ifndef SHADER_HPP
#define SHADER_HPP
#include "Libs.hpp"

class Shader
{
public:
    const GLuint shaderID;
    Shader(std::string name, GLenum shaderType); /**< name = name of the shader file in shaders subdir, without the path, with extension. */
    ~Shader();
};

 #endif // SHADER_HPP
