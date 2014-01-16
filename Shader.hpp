/**
 * \file Shader.hpp
 * \brief File with Shader class
 * \author GenaBitu
 **/

#ifndef SHADER_HPP
#define SHADER_HPP
#include "Libs.hpp"

/** \brief Shader class
 *
 * This class is used to load, store and use individual shaders.
 */
class Shader
{
public:
    const GLuint shaderID; /**< ID of the shader. */
    /** \brief Loads a shader
     * \param name Filename with extension, relative to the shaders subdir.
     * \param shaderType Type of the shader passed to glCreateShader() - see OpenGL documentation
     */
    Shader(std::string name, const GLenum shaderType);
    ~Shader();
};

 #endif // SHADER_HPP
