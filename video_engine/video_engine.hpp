#ifndef VIDEO_ENGINE_HPP
#define VIDEO_ENGINE_HPP

#include "../types_consts/sdl_type.hpp"
#include "../types_consts/graph_consts.hpp"
#include "../types_consts/hero_type.hpp"
#include "../types_consts/backs_type.hpp"
#include "../types_consts/fleet_type.hpp"
#include "../types_consts/test.hpp"
#include "../types_consts/text_type.hpp"
#include "../types_consts/text_consts.hpp"
#include "../types_consts/border_type.hpp"

using namespace my_sdl;
using namespace graph_consts;
using namespace classes;
using namespace backs_type;
using namespace fleet_type;
using namespace test;
using namespace text_type;
using namespace text_consts;
using namespace border_type;


void CLS(const sdl_t& sdl);
bool Init_sdl(sdl_t& sdl, const char* title);
void Close_sdl(sdl_t& sdl);
void Draw_backs(backs_t& backs);
bool Init_pause(sdl_t& sdl, pause_t& pause);
void Close_pause(pause_t& pause);
void Draw_border(sdl_t& sdl, border_t& b);


#ifdef DRAW_INTERSECTS
    void Draw_heros(sdl_t& sdl, hero_t& hero);
    void Show_fleet(sdl_t& sdl, fleet_t& fleet);
#else   
    void Draw_heros(hero_t& hero);
    void Show_fleet(fleet_t& fleet);
#endif


#endif