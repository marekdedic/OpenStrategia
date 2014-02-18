/**
 * \file Program.hpp
 * \brief File with Program class
 * \author GenaBitu
 **/

#ifndef PROGRAM_HPP
#define PROGRAM_HPP
#include "Libs.hpp"

/** \brief Program class
 *
 * This class creates a shader program, Adds individual shaders, links the whole program and spits back programID to be passed to glUseProgram().
 */

class Program
{
public:
    const GLuint programID; /**< ID of the shader program. */
    Program();
    /** \brief Adds a shader to the program
     *
     * Has no effect unless Link() was called afterwards.
     * \param name Filename with extension, relative to the shaders subdir.
     * \param shaderType Type of the shader passed to glCreateShader() - see OpenGL documentation
     */
    void AddShader(const std::string name, const GLenum shaderType);
    /** \brief Links shader program
     *
     * After changing anything to the shader program, Link() must be called again.
     */
    void Link() const;
    /** \brief Program class destructor
     *
     * Deletes all dynamically allocated variables.
     */
    ~Program();
private:
    std::vector<Shader*> shaders; /**< Vector with pointers to all shaders in the shader program. */
};

 #endif // PROGRAM_HPP
