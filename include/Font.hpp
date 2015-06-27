/**
 * \file Font.hpp
 * \brief File with Font class
 * \author GenaBitu
 **/

#ifndef FONT_HPP
#define FONT_HPP
#include "Libs.hpp"

/** \brief Font class
 *
 * This class completely handles one font.
 */
class Font
{
public:
    FT_Face face;
    static FT_Error init();
    Font(std::string name);
    Font(const Font& other);
    Font& operator=(const Font& other);
protected:
    static FT_Library library;
    std::string fileName;
};

 #endif // FONT_HPP
