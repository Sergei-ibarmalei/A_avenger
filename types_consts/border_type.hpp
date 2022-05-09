#ifndef BORDER_TYPE_HPP
#define BORDER_TYPE_HPP

#include "border_consts.hpp"
#include "sdl_type.hpp"

using namespace border_consts;
using namespace my_sdl;

namespace border_type
{
    typedef struct 
    {
        void Draw_border(sdl_t& sdl)
        {
            SDL_SetRenderDrawColor (sdl.gRenderer, 0xFF, 0x0, 0x0, 0xFF);
            SDL_RenderDrawLineF(sdl.gRenderer, BORDER_LEFT, BORDER_UP, BORDER_RIGHT, BORDER_UP);
            SDL_RenderDrawLineF(sdl.gRenderer, BORDER_RIGHT, BORDER_UP, BORDER_RIGHT, BORDER_DOWN);
            SDL_RenderDrawLineF(sdl.gRenderer, BORDER_RIGHT, BORDER_DOWN, BORDER_LEFT, BORDER_DOWN);
            SDL_RenderDrawLineF(sdl.gRenderer, BORDER_LEFT, BORDER_DOWN, BORDER_LEFT, BORDER_UP);
        }
    }border_t;
}

#endif