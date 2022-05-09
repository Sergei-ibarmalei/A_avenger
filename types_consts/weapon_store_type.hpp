#ifndef WEAPON_STORE_TYPE_HPP
#define WEAPON_STORE_TYPE_HPP

#include "../classes/laser.hpp"
#include <list>
#include <iterator>

using namespace classes;

namespace weapon_store
{
    using Laser_store_list = std::list<Laser*>;
    using laser_iterator = std::list<Laser*>::iterator;

    typedef struct 
    {
       Laser_store_list* hero_laser_store   = nullptr;
       Laser_store_list* aliens_laser_store = nullptr; 

    } weapon_store_t;
}

#endif