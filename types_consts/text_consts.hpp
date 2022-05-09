#ifndef TEXT_CONSTS_HPP
#define TEXT_CONSTS_HPP

#include "sdl_type.hpp"

using namespace my_sdl;

namespace text_consts
{
    //enum class text_type {pause_text, gui_text,};

    const SDL_Color      pause_color     {0xF4, 0xA4, 0x60, 0xFF};
    const SDL_Color      pause_sub_color {0xFF, 0x0, 0x0, 0xFF};
    const int  PAUSE_SUB_SIZE  {40};
    const int  PAUSE_SIZE      {200};
}

#endif