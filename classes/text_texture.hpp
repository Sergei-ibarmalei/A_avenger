#ifndef TEXT_TEXTURE_HPP
#define TEXT_TEXTURE_HPP

#include "texture.hpp"

namespace classes
{
    using namespace my_sdl;

    class Text_texture : public Texture
    {
        private:
        TTF_Font*   gFont = nullptr;
        text_t      texts;
        void loadMediaText(const text_t& t);
        void loadFromFile(const text_t& t);

        public:
        Text_texture(SDL_Renderer* r, const text_t& texts);
        Text_texture(const Text_texture& ): Texture (nullptr) {}
        ~Text_texture();
    };
}


#endif