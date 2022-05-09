#ifndef BACKS_TYPES_HPP
#define BACKS_TYPES_HPP

#include "../classes/star.hpp"
#include "../classes/back_fon.hpp"

namespace backs_type
{
    using namespace classes;

    typedef struct 
    {
        Star* fast = nullptr;
        Star* slow = nullptr;
        Back_fon* fon = nullptr;
    } backs_t;


}

#endif