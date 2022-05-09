#include "myrand.hpp"

#define to_float static_cast<float>
#define to_double static_cast<double>

namespace myrand
{
    float getRandom(const float min, const float max)
    {
        static const double fraction = 1.0 / (to_double(RAND_MAX) + 1.0);
        return to_float(rand() * fraction * (max - min + 1) + min );
    }

    //Расчет рандомной скорости
    float get_alien_speed()
    {
        return getRandom(ALIEN_SPEED_MIN, ALIEN_SPEED_MAX);
    }
}

