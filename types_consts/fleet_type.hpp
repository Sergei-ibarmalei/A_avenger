#ifndef FLEET_TYPE_HPP
#define FLEET_TYPE_HPP

#include "../classes/alien_stright_one.hpp"

#include <list>
#include <iterator>

namespace fleet_type
{
    #ifdef FLEET_BY_LIST
        using fleet_list = std::list<Alien_stright_one*>;
        using fleet_iterator  = std::list<Alien_stright_one*>::iterator;
    #endif

    constexpr int STRIGHT_FLEET_COUNT {7};

    typedef struct 
    {
        #ifdef FLEET_BY_LIST
            fleet_list*  list = nullptr;
        #else
            Alien_stright_one* stright_fleet_arr = nullptr;
        #endif
    } fleet_t;
}


#endif