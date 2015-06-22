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
    #include "TextureDDS.hpp"
public:
    GLuint ID; /**< ID of the texture. */
    /** \brief Texture class default constructor
     *
     * Allocates memory for the texture.
     */
    Texture();
    /** \brief Texture class constructor
     *
     * Loads a texture.
     * \param name Filename with extension, relative to the textures subdir
     */
    Texture(std::string name);
    /** \brief Texture class copy constructor
     *
     * Copies the texture.
     * \param other Address of the Texture to copy
     */
    Texture(const Texture& other);
    /** \brief Texture class assignment operator
     *
     * Copies the texture.
     * \param other Address of the Texture to copy
     * \return Address of the new Texture
     */
    Texture& operator=(const Texture& other);
    /** \brief Texture renderer
     *
     * Prepares the texture to be used on a rendered object.
     * \param prg A shader program to use
     * \param texUnit A texture unit to use, for example GL_TEXTURE0
     * \param texUnitNumber Should be the same as the number in texUnit
     * \param uvMatrix Name of the uniform, which holds the texture matrix in the shader
     * \param sampler Name of the sampler, which handles the texture in the shader
     */
    void use(std::shared_ptr<Program> prg, GLenum texUnit, GLint texUnitNumber, std::string uvMatrix, std::string sampler);
    /** \brief Texture loader
     *
     * Physically loads the texture.
     * \param name Texture file name with extension, relative to the textures subdir
     * \return True when the Texture was loaded without errors, false otherwise
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
    glm::mat3 transformation; /**< Matrix which is applied on the UV coordinates. Can be used to rotate/flip... the Texture without changing the actual data. */
    std::unique_ptr<TextureBridge> implementation; /**< The actual implementation in the client filesystem. Look up Bridge design pattern for more information. */
};

 #endif // TEXTURE_HPP

