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
    /** \brief Texture class default constructor
     *
     * Allocates memory for the texture
     */
    Texture();
    /** \brief Texture class constructor
     *
     * Loads a texture
     * \param name Filename with extension, relative to the textures subdir.
     */
    Texture(std::string name);
    /** \brief Texture class copy constructor
     *
     * Copies the texture.
     * \param other Address of the Texture to copy.
     */
    Texture(const Texture& other);
    /** \brief Texture class assignment operator
     *
     * Copies the texture.
     * \param other Address of the Texture to copy.
     * \return Address of the new Texture.
     */
    Texture& operator=(const Texture& other);
    /** \brief Texture class destructor
     *
     * Deletes the texture.
     */
    ~Texture();
};

 #endif // TEXTURE_HPP

