#include "back_fon.hpp"

namespace classes
{
    Back_fon::Back_fon(SDL_Renderer* r, const HISTORY& h)
    {
        make_fon(r, h);
    }

    void Back_fon::Change_fon(const HISTORY& h)
    {
        if (texture)
        {
            delete texture;
            texture = nullptr;
        }
        make_fon(renderer, h);
    }

    void Back_fon::make_fon(SDL_Renderer* r, const HISTORY& h)
    {
        renderer = r;

        switch (h)
        {
            case HISTORY::intro:
            {
                texture = new Image_texture {renderer, BACK_INTRO}; break;
            }
            case HISTORY::first:
            {
                texture = new Image_texture{renderer, BACK_FIRST}; break;
            }
            case HISTORY::second:
            {
                texture = new Image_texture{renderer, BAKC_SECOND}; break;
            }
            default: {}
        }
    }

    void Back_fon::Draw()
    {
        texture->Render(ul_corner);
    }

    Back_fon::~Back_fon()
    {
        if (texture)
        {
            delete texture;
            texture = nullptr;
        }
    }

}
