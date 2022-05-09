#ifndef STAR_CONSTS_HPP
#define STAR_CONSTS_HPP

#include <string>

namespace star_consts
{
    constexpr int FAST_STAR_COUNT {3};
    constexpr int SLOW_STAR_COUNT {5};
    constexpr float FAST_STAR_SPEED {2.0f};
    constexpr float SLOW_STAR_SPEED {1.0f};

    const std::string STAR_FILE_NAME = "stars/one_star.png";
}

#endif