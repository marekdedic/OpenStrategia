/**
 * \file TextureDDS.hpp
 * \brief File with TextureDDS class
 * \author GenaBitu
 **/

#ifndef TEXTUREDDS_HPP
#define TEXTUREDDS_HPP
#include "Libs.hpp"
#include "TextureBridge.hpp"

/** \brief TextureDDS class
 *
 * Implements a DDS texture.
 */
class TextureDDS : public TextureBridge
{
public:
    /** \brief Load a Texture
     *
     * Loads a texture from a DDS file.
     * \param ID ID of the Texture
     * \param name Texture file name with extension .DDS, relative to the textures subdir
     * \return True when the Texture was loaded without errors, false otherwise
     */
    bool load(GLuint ID, std::string name) override final;
};

#endif // TEXTUREDDS_HPP
