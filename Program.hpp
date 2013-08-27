/**
 * @file Program.hpp
 * File with Program class
 * @author GenaBitu
 **/

#ifndef PROGRAM_HPP
#define PROGRAM_HPP
#include "Libs.hpp"

class Program
{
public:
    const GLuint programID;
    Program();
    void AddShader(std::string name, GLenum shaderType); /**< name = name of the shader file in shaders subdir, without the path, with extension. */
    void Link();
    void Use();
    ~Program();
private:
    std::vector<Shader*> shaders;
};

 #endif // PROGRAM_HPP
