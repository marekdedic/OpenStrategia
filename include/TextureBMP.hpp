/**
 * \file TextureBMP.hpp
 * \brief File with TextureBMP class
 * \author GenaBitu
 **/

#ifndef TEXTUREBMP_HPP
#define TEXTUREBMP_HPP
#include "Libs.hpp"
#include "TextureBridge.hpp"

/** \brief TextureBMP class
 *
 * Implements a BMP texture.
 */
class TextureBMP : public TextureBridge
{
public:
    /** \brief TextureBMP constructor
     *
     * Saves a pointer to the parent Texture.
     * \param parent The parent object, which the implementation belongs to.
     */
    TextureBMP(Texture* parent);
    /** \brief Load a Texture
     *
     * Loads a texture from a BMP file.
     * \param name Texture file name with extension .BMP, relative to the textures subdir
     * \return True when the Texture was loaded without errors, false otherwise
     */
    bool load(std::string name) override final;
};

#endif // TEXTUREBMP_HPP
