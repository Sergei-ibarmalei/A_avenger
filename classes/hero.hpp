//Класс героя, является потомком класса Ship

#ifndef HERO_HPP
#define HERO_HPP


#include "ship.hpp"
#include "../types_consts/hero_consts.hpp"
#include "../types_consts/test.hpp"
#include "../engine/crossing.hpp"


namespace classes
{
    using namespace hero_consts;
    using namespace test;
    using namespace graph_consts;

    class Hero : public Ship
    {
        private:
        rect_vect sprites;
        text_vect all_textures;
        Position  hero_position  = Position::center;
        Direction hero_direction = Direction::right;
        void make_sprites();
        void fill_intersect_vect();
        void recompute_intersect_vect();
        void set_bullet_start();

        public:
        Hero(SDL_Renderer* r);
        ~Hero();
        bool Is_created();
        void Reset_hero_position();
        void Draw_intersects(const sdl_t& sdl);
        void Move(const float speed);
        void Draw();
        void Goes_right() {hero_direction = Direction::right;}
        void Goes_left()  {hero_direction = Direction::left;}
        void Goes_up()    {hero_direction = Direction::up;}
        void Goes_down()  {hero_direction = Direction::down;}
        void Walk_stright(bool& is_walk_stright);
        

    };
}

#endif