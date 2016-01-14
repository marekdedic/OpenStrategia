/**
 * \file Shader.hpp
 * \brief File with Shader class
 * \author GenaBitu
 **/

#pragma once

#include "../Global.hpp"

/** \brief Shader class
 *
 * This class is used to load, store and use individual shaders.
 */
class Shader
{
public:
    const GLuint ID; /**< ID of the shader */
    Shader() = delete;
    /** \brief Loads a shader.
     * \param name Filename with extension, relative to the shaders subdir
     * \param shaderType Type of the shader passed to glCreateShader() - see OpenGL documentation
     */
    Shader(std::string name, const GLenum shaderType);
    /** \brief Shader class destructor
     *
     * Deletes shader.
     */
    ~Shader();
};
