/**
 * \file TextureBridge.hpp
 * \brief File with TextureBridge class
 * \author GenaBitu
 **/

#ifndef TEXTUREBRIDGE_HPP
#define TEXTUREBRIDGE_HPP
#include "Libs.hpp"

/** \brief TextureBridge class
 *
 * This class is used as an abstract parent to all texture implementations.
 */
class TextureBridge
{
public:
    /** \brief Load a Texture
     *
     * Loads a texture from the corresponding file.
     * \param ID ID of the Texture
     * \param name Texture file name with extension .BMP, relative to the textures subdir
     * \return True when the Texture was loaded without errors, false otherwise
     */
    virtual bool load(GLuint ID, std::string name) = 0;
    /** \brief Empty destructor
     *
     * Allows for overriding, does nothing.
     */
    virtual ~TextureBridge();
};

#endif // TEXTUREBRIDGE_HPP
