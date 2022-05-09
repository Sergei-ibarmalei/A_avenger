#include "image_texture.hpp"

namespace classes
{
    Image_texture::Image_texture() : Texture(nullptr)
    {
        renderer = nullptr;
    }

    Image_texture::Image_texture(SDL_Renderer* r, const string_ name) : Texture (r)
    {
        file_name = name;
        loadFromFile();
    }

    Image_texture::~Image_texture()
    {
        free();
    }

    void Image_texture::loadFromFile()
    {
        free();
        SDL_Texture* newTexture = nullptr;
        SDL_Surface* loadedSurface = IMG_Load(file_name.c_str());
        if (!loadedSurface)
        {
            std::cout << "Unable to load image " << file_name << " error: " << IMG_GetError() << '\n';
            texture = nullptr;
            return;
        }
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (!newTexture)
        {
            std::cout << "Unable to create texture from " << file_name << " " << SDL_GetError() << '\n';
            return;
        }
        texture_w  = static_cast<float>(loadedSurface->w);
        texture_h = static_cast<float>(loadedSurface->h);
        SDL_FreeSurface(loadedSurface);
        texture = newTexture;
    }
}

