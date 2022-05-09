//Класс лазер

#ifndef LASER_HPP
#define LASER_HPP

#include "image_texture.hpp"
#include "../types_consts/weapon_type.hpp"
#include "../types_consts/border_consts.hpp"

using namespace border_consts;
using namespace weapon_type;

namespace classes
{
    class Laser
    {
        private:
        Laser_kind laser_kind;
        DIRECTION  laser_direction = DIRECTION::none;
        plot_t ul_corner;
        bool is_visible = true;
        Image_texture* texture = nullptr;
        float laser_width;
        SDL_FRect* intersect_rect = nullptr;
        void recompute_intersect();

        public:
        Laser(SDL_Renderer* r, const Laser_kind& kind, const plot_t& start_, const DIRECTION& dir);
        Laser(const Laser& ) {}
        ~Laser();
        void Draw_intersect(const sdl_t& sdl);
        void Draw();
        void Move();
        bool& Is_visible() {return is_visible;} 
        bool Is_created() {return texture != nullptr;}
        SDL_FRect* Laser_intersect_rect() const {return intersect_rect;}
    };
}


#endif