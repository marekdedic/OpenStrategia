/**
 * \file TextureBMP.hpp
 * \brief File with TextureBMP class
 * \author GenaBitu
 **/

#pragma once

#include "../Global.hpp"
#include "TextureBridge.hpp"

#pragma pack(push)
#pragma pack(1)

typedef struct {
    char magic[2];
    uint32_t fileSize;
    uint32_t reserved0;
    uint32_t dataOffset;
    uint32_t headerSize;    // 40
    uint32_t width;
    uint32_t height;
    uint16_t numPlanes;     // 1
    uint16_t BPP;           // Bits per pixel
    uint32_t compression;   // 0
    uint32_t imageSize;
    uint32_t hRes;          // In pixels per meter
    uint32_t vRes;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
} BMP_HEADER;

#pragma pack(pop)

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
