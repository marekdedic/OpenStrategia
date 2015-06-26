#include "../Main.hpp"
using namespace std;
using namespace glm;

FT_Library Font::library{};

int Font::init()
{
    return FT_Init_FreeType(&library);
}
