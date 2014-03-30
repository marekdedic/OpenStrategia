/**
 * \file Texture.hpp
 * \brief File with Texture class
 * \author GenaBitu
 **/

#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include "Libs.hpp"

/** \brief Texture class
 *
 * This class is used to load, store and use individual texture.
 */
class Texture
{
public:
    GLuint textureID; /**< ID of the texture. */
    /** \brief Loads a texture
     * \param name Filename with extension, relative to the textures subdir.
     */
    Texture(std::string name);
    ~Texture();
};

 #endif // TEXTURE_HPP

