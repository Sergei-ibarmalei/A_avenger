//Абстрактный базовый класс
//для всех классов кораблей


#ifndef SHIP_HPP
#define SHIP_HPP

#include "../types_consts/graph_consts.hpp"
#include "../types_consts/vects_type.hpp"
#include "image_texture.hpp"

namespace classes
{

    using namespace my_sdl;
    using namespace vect_type;
    enum class Direction {right, left, up, down,};

    class Ship
    {
        protected:

        plot_t   ul_corner    {0.0f, 0.0f};
        plot_t   bullet_start {0.0f, 0.0f};
        frect_vect intersect_vect;
        bool     ship_is_visible = true;
        virtual void set_bullet_start() {}
        virtual void fill_intersect_vect()      = 0;
        virtual void recompute_intersect_vect() = 0;


        public:

        Ship() {}
        virtual ~Ship() {}
        plot_t& UL_corner()    {return ul_corner;}
        plot_t& Bullet_start() {return bullet_start;}
        virtual void Draw() = 0;
        virtual void Draw_intersects(const sdl_t&) {}
        virtual void Move(const float) {}
        virtual bool Is_created() = 0;
        frect_vect& get_intersect_vect() {return intersect_vect;}
        bool& Ship_is_visible() {return ship_is_visible;}


    };



}

#endif





