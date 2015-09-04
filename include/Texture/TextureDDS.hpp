/**
 * \file TextureDDS.hpp
 * \brief File with TextureDDS class
 * \author GenaBitu
 **/

#ifndef TEXTUREDDS_HPP
#define TEXTUREDDS_HPP
#include "../Global.hpp"
#include "TextureBridge.hpp"

#define DDS_FOURCC_DXT1 0x31545844 // ASCII-encoded name
#define DDS_FOURCC_DXT3 0x33545844
#define DDS_FOURCC_DXT5 0x35545844
#define DDS_FOURCC_BC4U 0x55344342
#define DDS_FOURCC_BC4S 0x53344342
#define DDS_FOURCC_BC5S 0x53354342

#pragma pack(push)
#pragma pack(1)

typedef struct {
    unsigned long low;
    unsigned long high;
} DDS_COLORKEY;

typedef struct {
    unsigned long structSize;   // 32
    unsigned long flags;
    unsigned long fourCC;
    unsigned long RGBBitCount;
    unsigned long RBitMask;
    unsigned long GBitMask;
    unsigned long BBitMask;
    unsigned long ABitMask;
} DDS_PIXELFORMAT;

typedef struct {
    char magic[4];
    unsigned long structSize;   // 124
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

#pragma pack(pop)

/** \brief TextureDDS class
 *
 * Implements a DDS texture.
 */
class TextureDDS : public TextureBridge
{
public:
    /** \brief TextureDDS constructor
     *
     * Saves a pointer to the parent Texture.
     * \param parent The parent object, which the implementation belongs to.
     */
    TextureDDS(Texture* parent);
    /** \brief Load a Texture
     *
     * Loads a texture from a DDS file.
     * \param name Texture file name with extension .DDS, relative to the textures subdir
     * \return True when the Texture was loaded without errors, false otherwise
     */
    bool load(std::string name) override final;
};

#endif // TEXTUREDDS_HPP
