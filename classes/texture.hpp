//Родительский класс Texture
//Потомок классов Image_texture, Text_texture


#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "../types_consts/sdl_type.hpp"

using namespace my_sdl;

namespace classes
{

    class Texture
    {
        protected:
        SDL_Renderer*  renderer = nullptr;
        SDL_Texture*   texture  = nullptr;
        float texture_w;
        float texture_h;
        void free();


        public:
        Texture(SDL_Renderer* r);
        Texture(const Texture& ) {}
        void Render(const plot_t& corner, SDL_Rect* clip = nullptr);
        virtual ~Texture() {}
        bool Texture_is_created() {return texture != nullptr;}
        float Get_texture_w() const {return texture_w;}
        float Get_texture_h() const {return texture_h;}
    };

}


#endif