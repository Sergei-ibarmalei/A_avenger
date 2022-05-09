#ifndef SDL_TYPE_HPP
#define SDL_TYPE_HPP


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

#include "game_consts.hpp"



namespace my_sdl
{
    using string_ = std::string;
    using namespace game_consts;

    typedef struct
    {
        SDL_Renderer*      gRenderer = nullptr;
        SDL_Window*        gWindow   = nullptr;
        SDL_Event e;
        bool sdl_ok                  = true;
        bool game_pause              = false;
        bool game_quit               = false;
        HISTORY history              {HISTORY::intro};
    } sdl_t;

    typedef struct
    {
        float x;
        float y;
    } plot_t;


    typedef struct
    {
        SDL_Color        color;
        int              text_size;
        string_          text;
        const char*      text_font = "sfns-display-bold.ttf";

    } text_t;

    //Тип - реперные точки для кривой безье
    typedef struct
    {
        plot_t p0;
        plot_t p1;
        plot_t p2;
        plot_t p3;
    } repers_t;
}



#endif
