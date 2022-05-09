#include "text_texture.hpp"


namespace classes
{
    Text_texture::Text_texture(SDL_Renderer* r, const text_t& texts) : Texture(r)
    {
        loadMediaText(texts);
        if (!gFont) return;
        loadFromFile(texts);
    }

    void Text_texture::loadFromFile(const text_t& t)
    {
        free();
        SDL_Texture* newTexture = nullptr;
        SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, t.text.c_str(), t.color);
        if (!textSurface)
        {
            std::cout << "Unable to render text surface, erro: " << TTF_GetError() << "\n";
            return;
        }
        newTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (!newTexture)
        {
            std::cout << "Unable to create texture form text, abort\n";
            return;
        }
        texture_w  = static_cast<float>(textSurface->w);
        texture_h = static_cast<float>(textSurface->h);
        SDL_FreeSurface(textSurface);
        texture = newTexture;
    }

    void Text_texture::loadMediaText(const text_t& t)
    {
        gFont = TTF_OpenFont(t.text_font, t.text_size);
        if (!gFont)
        {
            std::cout << "Failed to open font, error: " << TTF_GetError() << '\n';
        }
    }

    Text_texture::~Text_texture()
    {
        free();
    }
}

