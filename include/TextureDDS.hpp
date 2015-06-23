/**
 * \file TextureDDS.hpp
 * \brief File with TextureDDS class
 * \author GenaBitu
 **/

#ifndef TEXTUREDDS_HPP
#define TEXTUREDDS_HPP
#include "Libs.hpp"
#include "TextureBridge.hpp"

typedef struct {
    unsigned long low;
    unsigned long high;
} DDS_COLORKEY;

typedef struct {
    unsigned long structSize;
    unsigned long flags;
    unsigned long fourCC;
    unsigned long RGBBitCount;
    unsigned long RBitMask;
    unsigned long GBitMask;
    unsigned long BBitMask;
    unsigned long ABitMask;
} DDS_PIXELFORMAT;

typedef struct {
    unsigned long structSize;
    unsigned long flags;
    unsigned long height;
    unsigned long width;
    unsigned long linearSize;
    unsigned long depth;
    unsigned long mipmapCount;
    unsigned long alphaBitDepth;
    unsigned long reserved0[2];
    DDS_COLORKEY destOverlay;
    DDS_COLORKEY destBlit;
    DDS_COLORKEY srcOverlay;
    DDS_COLORKEY srcBlit;
    DDS_PIXELFORMAT pixelFormat;
    unsigned long caps[4];
    unsigned long reserved1;
} DDS_HEADER;

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
