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
protected:
    static FT_Library library;
};

 #endif // FONT_HPP
