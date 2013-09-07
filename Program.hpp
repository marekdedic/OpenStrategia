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
    void AddShader(const std::string name, const GLenum shaderType); /**< name = name of the shader file in shaders subdir, without the path, with extension. */
    void Link() const;
    ~Program();
private:
    std::vector<Shader*> shaders;
};

 #endif // PROGRAM_HPP
