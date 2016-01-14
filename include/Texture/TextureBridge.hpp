/**
 * \file TextureBridge.hpp
 * \brief File with TextureBridge class
 * \author GenaBitu
 **/

#pragma once

#include "../Global.hpp"

/** \brief TextureBridge class
 *
 * This class is used as an abstract parent to all texture implementations.
 */
class TextureBridge
{
public:
    Texture* parent;
    TextureBridge() = delete;
    /** \brief TextureBridge constructor
     *
     * Saves a pointer to the parent Texture.
     * \param parent The parent object, which the implementation belongs to.
     */
    TextureBridge(Texture* parent);
    /** \brief TextureBridge class copy constructor
     *
     * Copies the texture implementation object.
     * \param other Address of the TextureBridge to copy
     */
    TextureBridge(const TextureBridge& other);
    /** \brief TextureBridge class assignment operator
     *
     * Copies the texture implementation object.
     * \param other Address of the TextureBridge to copy
     * \return Address of the new TextureBridge
     */
    TextureBridge& operator=(const TextureBridge& other);
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
    std::string fileName;
};
