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
    virtual bool load(GLuint ID, std::string name) = 0;
    virtual ~TextureBridge();
};

#endif // TEXTUREBRIDGE_HPP
