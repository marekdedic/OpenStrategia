/**
 * \file Font.hpp
 * \brief File with Font class
 * \author GenaBitu
 **/

#pragma once

#include "Global.hpp"

/** \brief Font class
 *
 * This class completely handles one font.
 */
class Font
{
public:
    FT_Face face;
    FT_Bool kerning;
    static FT_Error init();
    static void done();
    Font(std::string name);
    Font(const Font& other);
    Font& operator=(const Font& other);
protected:
    static FT_Library library;
    std::string fileName;
};
