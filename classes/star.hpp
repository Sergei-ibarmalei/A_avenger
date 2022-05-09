#ifndef STAR_HPP
#define STAR_HPP

#include "../types_consts/sdl_type.hpp"
#include "../types_consts/graph_consts.hpp"
#include "../types_consts/star_consts.hpp"
#include "../types_consts/border_consts.hpp"
#include "../engine/myrand.hpp"
#include "../engine/crossing.hpp"
#include "image_texture.hpp"

namespace classes
{
   
    using namespace my_sdl;
    using namespace classes;
    using namespace star_consts;
    using namespace myrand;
    using namespace graph_consts;
    using namespace crossing;
    using namespace border_consts;


    class Star
    {
        private:
        plot_t ul_corner;
        Image_texture*    texture = nullptr;

        public:
        Star();
        ~Star();
        Star(const Star& ) {}
        void Make_star(SDL_Renderer* r);
        void Draw();
        void Move(const float speed);
        bool Is_init() {return texture != nullptr;}

        
    };


}


#endif