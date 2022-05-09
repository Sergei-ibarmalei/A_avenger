#ifndef HERO_CONSTS_HPP
#define HERO_CONSTS_HPP

#define to_ushort static_cast<unsigned short>

#include "sdl_type.hpp"

namespace hero_consts
{
    using namespace my_sdl;

    enum class Position {up, center, down, all,};

    constexpr plot_t HERO_START {-100.0f, 540.0f};
    constexpr float    HERO_SPEED {5.0f};
    const string_ HERO_FILE_UP     = "ships/small_1.png";
    const string_ HERO_FILE_DOWN   = "ships/small_3.png";
    const string_ HERO_FILE_CENTER = "ships/small_2.png";

    constexpr unsigned short POSITION_CENTER = to_ushort(Position::center);
    constexpr unsigned short POSITION_UP     = to_ushort(Position::up);
    constexpr unsigned short POSITION_DOWN   = to_ushort(Position::down);
    const unsigned HERO_STRIGHT_LENGTH            {300};
    constexpr int HERO_STOP_WALKING_STRIGHT_X      {200};
    constexpr int HERO_WALKING_STRIGHT_SPEED      {7};
    constexpr int HERO_WEAPON_START_SHIFTX        {10};
    constexpr int HERO_INTERSECTION_RECTS_LENGTH  {2};
    constexpr float FIRST_INTERSECTION_RECT_WIDTH   {135.0f};
    constexpr float FIRST_INTERSECTION_RECT_SHIFTY  {17.0f};
    constexpr float FIRST_INTERSECTION_RECT_HEIGHT  {23.0f};
    constexpr float SECOND_INTERSECTION_RECT_WIDTH  {37.0f};
    constexpr float SECOND_INTERSECTION_RECT_HEIGHT {53.0f};
    constexpr float SECOND_INTERSECTION_RECT_SHIFTX {13.0f};


    const int CENTER_SPRITE {1};

}

#endif