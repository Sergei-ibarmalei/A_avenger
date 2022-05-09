//Прямолетающий алиен

#ifndef ALIEN_STRIGHT_ONE_HPP
#define ALIEN_STRIGHT_ONE_HPP

#include "ship.hpp"
//#include "../types_consts/visibility_vects.hpp"
#include "../types_consts/aliens_consts.hpp"
#include "../types_consts/graph_consts.hpp"
#include "../types_consts/border_consts.hpp"
#include "../types_consts/test.hpp"
#include "../engine/myrand.hpp"

#define to_float static_cast<float>
#define behind_right ul_corner.x >= BORDER_RIGHT
#define behind_left  (ul_corner.x + texture->Get_texture_w()) < BORDER_LEFT

using namespace aliens_consts;
using namespace graph_consts;
using namespace myrand;
using namespace border_consts;
using namespace test;

namespace classes
{

    class Alien_stright_one : public Ship
    {
        private:
        Image_texture*   texture = nullptr;
        float alien_speed = 0.0f;
        void fill_intersect_vect();
        void recompute_intersect_vect();
        

        public:
        Alien_stright_one();
        ~Alien_stright_one();
        Alien_stright_one(const Alien_stright_one&) {}
        void Make_alien(SDL_Renderer* r);
        void Draw();
        void Draw_intersects(const sdl_t& sdl);
        void Move(const float speed);
        bool Is_created();
        void Make_new_ulcorner();
        bool Alien_is_outofscreen();
        float Alien_speed() const {return alien_speed;}
        void Set_speed(const float s) {alien_speed = s;}
    };


}

#endif