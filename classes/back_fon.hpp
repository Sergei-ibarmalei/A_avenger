#ifndef BACK_FON_HPP
#define BACK_FON_HPP

#include "../types_consts/backfon_consts.hpp"
#include "../types_consts/game_consts.hpp"
#include "../types_consts/border_consts.hpp"
#include "image_texture.hpp"

using namespace backfon_consts;
using namespace border_consts;

namespace classes
{
    class Back_fon
    {
        private:
        plot_t ul_corner = {0.0f, BORDER_UP};
        HISTORY history = HISTORY::first;
        Image_texture* texture  = nullptr;
        SDL_Renderer*  renderer = nullptr;
        void make_fon(SDL_Renderer* r, const HISTORY& h);

        public:
        Back_fon(SDL_Renderer* r, const HISTORY& h);
        Back_fon(const Back_fon& ) {}
        ~Back_fon();
        bool Is_init() {return texture != nullptr;}
        void Change_fon(const HISTORY& h);
        void Draw();
    };
}


#endif