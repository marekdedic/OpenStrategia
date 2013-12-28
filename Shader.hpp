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
    Shader(std::string name, const GLenum shaderType);
    ~Shader();
};

 #endif // SHADER_HPP
