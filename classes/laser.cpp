#include "laser.hpp"

#define laser_out_left (ul_corner.x + laser_width) < 0
#define laser_out_right (ul_corner.x > S_W)

namespace classes
{


    Laser::Laser(SDL_Renderer* r, const Laser_kind& kind, const plot_t& start_, const DIRECTION& dir)
    {
        switch (kind)
        {
            case Laser_kind::red:
            {
                texture = new Image_texture {r, LASER_RED_FILE}; break;
            }
            case Laser_kind::green:
            {
                texture = new Image_texture {r, LASER_GREEN_FILE}; break;
            }
            case Laser_kind::blue:
            {
                texture = new Image_texture {r, LASER_BLUE_FILE}; break;
            }
            default: {}
        }
        laser_width = texture->Get_texture_w();
        ul_corner = start_;
        laser_direction = dir;
        intersect_rect = new SDL_FRect {ul_corner.x, ul_corner.y, texture->Get_texture_w(), texture->Get_texture_h()};
    }

    void Laser::recompute_intersect()
    {
        intersect_rect->x = ul_corner.x;
        intersect_rect->y = ul_corner.y;
    }

    Laser::~Laser()
    {
        if (texture)
        {
            delete texture;
            texture = nullptr;
        }
        if (intersect_rect)
        {
            delete intersect_rect;
            intersect_rect = nullptr;
        }
    }

    void Laser::Move()
    {
        if (!is_visible) return;

        switch (laser_direction)
        {
            case DIRECTION::right:
            {
                ul_corner.x += LASER_SPEED; break;
            }
            case DIRECTION::left:
            {
                ul_corner.x -= LASER_SPEED; break;
            }
            case DIRECTION::up:
            case DIRECTION::down:
            default: {}
        }
        recompute_intersect();
        if (laser_out_left || laser_out_right) is_visible = false;
        
    }

    void Laser::Draw()
    {
        texture->Render(ul_corner);
    }

    void Laser::Draw_intersect(const sdl_t& sdl)
    {
        SDL_SetRenderDrawColor(sdl.gRenderer, 0xFF, 0x0, 0x0, 0xFF);
        SDL_RenderDrawRectF(sdl.gRenderer, intersect_rect);
    }


}

