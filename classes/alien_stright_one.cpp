#include "alien_stright_one.hpp"


namespace classes
{

    plot_t get_random_ulcorner();

    Alien_stright_one::Alien_stright_one()
    {
        #ifdef ALIEN_STRIGHT_ONE_TEST
            ul_corner.x = to_float((S_W / 2) + 100);
            ul_corner.y = to_float((S_H / 2) - 20);
        #else
            //ul_corner.x = to_float(getRandom(S_W, S_W + 400));
            //ul_corner.y = to_float(getRandom(100, S_H - 200));
        #endif
    }

    void Alien_stright_one::Make_new_ulcorner()
    {
        ul_corner = get_random_ulcorner();
        recompute_intersect_vect();
    }

    //Делаем текстуру для пришельца
    void Alien_stright_one::Make_alien(SDL_Renderer* r)
    {
        texture = new Image_texture {r, ALIEN_STRIGHT_ONE_FILE};
        fill_intersect_vect();
    }

    Alien_stright_one::~Alien_stright_one()
    {
        if (texture)
        {
            delete texture;
            texture = nullptr;
        }
    }

    bool Alien_stright_one::Is_created()
    {
        return texture != nullptr;
    }

    void Alien_stright_one::Draw()
    {
        if (ship_is_visible) texture->Render(ul_corner);
    }

    void Alien_stright_one::Draw_intersects(const sdl_t& sdl)
    {
        for (auto rect : intersect_vect)
        {
            SDL_SetRenderDrawColor(sdl.gRenderer, 0xFF, 0x0, 0x0, 0xFF);
            SDL_RenderDrawRectF(sdl.gRenderer, rect);
        }
    }

    void Alien_stright_one::fill_intersect_vect()
    {
        SDL_FRect* first_rect = 
        new SDL_FRect {ul_corner.x, ul_corner.y + 31,
                      76.0f, 14.0f};

        SDL_FRect* second_rect = 
        new SDL_FRect {ul_corner.x + 42.0f, ul_corner.y + 48.0f,
                      33.0f, 12.0f};

        SDL_FRect* third_rect = 
        new SDL_FRect {ul_corner.x + 53.0f, ul_corner.y + 61.0f,
                       20.0f, 17.0f};

        SDL_FRect* fourth_rect = 
        new SDL_FRect {ul_corner.x + 42.0f, ul_corner.y + 18.0f,
                       33.0f, 12.0f};

        SDL_FRect* fifth_rect = 
        new SDL_FRect {ul_corner.x + 53.0f, ul_corner.y,
                       20.0f, 17.0f};
                       
        intersect_vect.push_back(first_rect);
        intersect_vect.push_back(second_rect);
        intersect_vect.push_back(third_rect);
        intersect_vect.push_back(fourth_rect);
        intersect_vect.push_back(fifth_rect);

    }

    void Alien_stright_one::recompute_intersect_vect()
    {
        intersect_vect[0]->x = ul_corner.x;
        intersect_vect[0]->y = ul_corner.y + 31.0f;

        intersect_vect[1]->x = ul_corner.x + 42.0f; 
        intersect_vect[1]->y = ul_corner.y + 48.0f;

        intersect_vect[2]->x = ul_corner.x + 53.0f;
        intersect_vect[2]->y = ul_corner.y + 61.0f;

        intersect_vect[3]->x = ul_corner.x + 42.0f;
        intersect_vect[3]->y = ul_corner.y + 18.0f;

        intersect_vect[4]->x = ul_corner.x + 53.0f;
        intersect_vect[4]->y = ul_corner.y;
    }



    void Alien_stright_one::Move(const float speed)
    {
        if (!ship_is_visible) return;
        ul_corner.x -= speed;
        recompute_intersect_vect();
    } 

    bool Alien_stright_one::Alien_is_outofscreen()
    {
        return behind_left;
    }


    //Получаем рандомную координату
    plot_t get_random_ulcorner()
    {
        plot_t p;
        p.x = to_float(getRandom(S_W, S_W + 1000));
        p.y = to_float(getRandom(100, S_H - 100));
        return p;
    }

 
}