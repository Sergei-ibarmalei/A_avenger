#ifndef HERO_TYPE_HPP
#define HERO_TYPE_HPP

#include "../classes/hero.hpp"

using namespace classes;

typedef struct 
{
    Hero*  hero         = nullptr; 
    #ifdef HERO_AT_CENTER   
          bool walk_stright = false;
    #else 
        bool walk_stright = true;
    #endif
} hero_t;


#endif