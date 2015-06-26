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
    static FT_Error init();
    Font(std::string name);
    std::shared_ptr<Image> render(char c);
protected:
    static FT_Library library;
    std::string fileName;
    FT_Face face;
};

 #endif // FONT_HPP
