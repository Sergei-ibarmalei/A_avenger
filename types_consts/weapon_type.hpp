#ifndef WEAPON_TYPE_HPP
#define WEAPON_TYPE_HPP

#include <string>

namespace weapon_type
{
    enum class Weapon_kind {laser, bullet, rocket,};
    enum class Laser_kind  {red, green, blue,};

    const std::string LASER_RED_FILE = "lasers/laserRed01.png";
    const std::string LASER_GREEN_FILE = "lasers/laserGreen03.png";
    const std::string LASER_BLUE_FILE = "lasers/laserBlue01.png";

    constexpr float LASER_SPEED {12.0f};


    

}




#endif