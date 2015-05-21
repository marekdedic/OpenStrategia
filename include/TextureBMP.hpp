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
    bool load(GLuint ID, std::string name) override final;
};

#endif // TEXTUREBMP_HPP
