#include "crossing.hpp"
#include "../types_consts/border_consts.hpp"

namespace crossing
{
    using namespace border_consts;
    
    bool is_crossing_right(const float x)
    {
        return x > BORDER_RIGHT;
    }

    bool is_crossing_left(const float x)
    {
        return x < BORDER_LEFT;
    }

    bool is_crossing_up(const float x)
    {
        return x < BORDER_UP;
    }

    bool is_crossing_down(const float x)
    {
        return x > BORDER_DOWN;
    }
}