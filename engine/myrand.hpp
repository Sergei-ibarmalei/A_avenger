#ifndef MYRAND_HPP
#define MYRAND_HPP

#include "../types_consts/aliens_consts.hpp"
#include <cstdlib>

using namespace aliens_consts;

namespace myrand
{
    float getRandom(const float min, const float max);
    float get_alien_speed();
}

#endif