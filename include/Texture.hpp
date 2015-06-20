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
    #include "TextureBMP.hpp"
public:
    GLuint ID; /**< ID of the texture. */
    glm::mat3 transformation;
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
    /** \brief Texture loader
     *
     * Physically loads the texture.
     */
    bool load(std::string name);
    /** \brief Horizontally flip Texture
     *
     * Changes Texture y axis orientation.
     */
    void hflip();
    /** \brief Vertically flip Texture
     *
     * Changes Texture x axis orientation.
     */
    void vflip();
    /** \brief Texture class destructor
     *
     * Deletes the texture.
     */
    ~Texture();
private:
    std::unique_ptr<TextureBridge> implementation;
};

 #endif // TEXTURE_HPP

