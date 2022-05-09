#ifndef VECTS_TYPE_HPP
#define VECTS_TYPE_HPP

#include "../classes/image_texture.hpp"
#include "sdl_type.hpp"
#include <vector>

using namespace classes;
using namespace my_sdl;

namespace vect_type
{
    using frect_vect = std::vector<SDL_FRect*>;
    using rect_vect  = std::vector<SDL_Rect*>;
    using text_vect  = std::vector<Texture*>;
}


#endif
