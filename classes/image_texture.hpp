//Класс текстуры
//Наследуется от класса Texture


#ifndef IMAGE_TEXTURE_HPP
#define IMAGE_TEXTURE_HPP

#include "texture.hpp"

namespace classes
{
    class Image_texture : public Texture 
    {
        private:
        string_ file_name;
        void loadFromFile();

        public:
        Image_texture();
        Image_texture(SDL_Renderer* r, const string_ name);
        Image_texture(const Image_texture& ): Texture(nullptr) {}
        ~Image_texture();
        void Set_renderer(SDL_Renderer* r)    {renderer = r;}
        void Set_filename(const string_ name) {file_name = name;}

    };
}



#endif