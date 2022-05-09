#include "texture.hpp"

namespace classes
{
    Texture::Texture(SDL_Renderer* r)
    {
        renderer = r;
    }

    void Texture::free()
    {
        if (texture)
        {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
}

    void Texture::Render(const plot_t& corner, SDL_Rect* clip)
    {
        SDL_FRect renderQuad = {corner.x, corner.y, texture_w, texture_h};
        if (clip)
        {
            renderQuad.w = clip->w;
            renderQuad.h = clip->h;
        }
        SDL_RenderCopyF(renderer, texture, clip, &renderQuad);
    }
}





