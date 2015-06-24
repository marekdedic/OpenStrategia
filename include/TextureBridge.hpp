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
    TextureBridge() = delete;
    /** \brief TextureBridge constructor
     *
     * Saves a pointer to the parent Texture.
     * \param parent The parent object, which the implementation belongs to.
     */
    TextureBridge(Texture* parent);
    /** \brief Load a Texture
     *
     * Loads a texture from the corresponding file.
     * \param name Texture file name with extension .BMP, relative to the textures subdir
     * \return True when the Texture was loaded without errors, false otherwise
     */
    virtual bool load(std::string name) = 0;
    /** \brief Empty destructor
     *
     * Allows for overriding, does nothing.
     */
     virtual ~TextureBridge();
protected:
    Texture* parent;
    std::string fileName;
};

#endif // TEXTUREBRIDGE_HPP
