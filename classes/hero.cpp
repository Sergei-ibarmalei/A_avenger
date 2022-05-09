#include "hero.hpp"

#define to_float static_cast<float>
#define to_int   static_cast<int>
#define hero_in_work_position ul_corner.x > HERO_STOP_WALKING_STRIGHT_X
#define stop_walk_stright is_walk_stright = false
#define first_texture_created all_textures[POSITION_UP]->Texture_is_created()
#define second_texture_created all_textures[POSITION_CENTER]->Texture_is_created()
#define third_texture_created all_textures[POSITION_DOWN]->Texture_is_created()
#define all_textures_are_created first_texture_created && second_texture_created && third_texture_created

using namespace crossing;

namespace classes
{
    Hero::Hero(SDL_Renderer* r) : Ship ()
    {
        #ifdef HERO_AT_CENTER
            ul_corner = {S_W/2 - 50, S_H/2};
        #else
            ul_corner = HERO_START;
        #endif
        all_textures.push_back(new Image_texture{r, HERO_FILE_UP});
        all_textures.push_back(new Image_texture{r, HERO_FILE_CENTER});
        all_textures.push_back(new Image_texture{r, HERO_FILE_DOWN});
        make_sprites();
        fill_intersect_vect();
        set_bullet_start();
    }

    Hero::~Hero()
    {
        for (auto rect : sprites)
        {
            delete rect;
            rect = nullptr;
        }

        for (auto rect : intersect_vect)
        {
            delete rect;
            rect = nullptr;
        }

        for (auto textures : all_textures)
        {
            delete textures;
            textures = nullptr;
        }
    }

    void Hero::make_sprites()
    {
        for (size_t i = 0; i < static_cast<size_t>(Position::all); i ++)
        {
            sprites.push_back(new SDL_Rect {});
        }

        sprites[POSITION_UP]->x = 3;
        sprites[POSITION_UP]->y = 23;
        sprites[POSITION_UP]->w = 137;
        sprites[POSITION_UP]->h = 48;

        sprites[POSITION_CENTER]->x = 3;
        sprites[POSITION_CENTER]->y = 19;
        sprites[POSITION_CENTER]->w = 137;
        sprites[POSITION_CENTER]->h = 56;

        sprites[POSITION_DOWN]->x = 3;
        sprites[POSITION_DOWN]->y = 24;
        sprites[POSITION_DOWN]->w = 137;
        sprites[POSITION_DOWN]->h = 48;

      
    }

    void Hero::fill_intersect_vect()
    {
        SDL_FRect* intersect_rect_0  = new SDL_FRect {};
        intersect_rect_0->x = ul_corner.x + to_float(sprites[CENTER_SPRITE]->x);
        intersect_rect_0->y = ul_corner.y + to_float(FIRST_INTERSECTION_RECT_SHIFTY);
        intersect_rect_0->w = FIRST_INTERSECTION_RECT_WIDTH;
        intersect_rect_0->h = FIRST_INTERSECTION_RECT_HEIGHT;
        intersect_vect.push_back(intersect_rect_0);

        SDL_FRect* intersect_rect_1 = new SDL_FRect {};
        intersect_rect_1->x = ul_corner.x + SECOND_INTERSECTION_RECT_SHIFTX;
        intersect_rect_1->y = ul_corner.y;
        intersect_rect_1->w = SECOND_INTERSECTION_RECT_WIDTH;
        intersect_rect_1->h = SECOND_INTERSECTION_RECT_HEIGHT;
        intersect_vect.push_back(intersect_rect_1);
    }

    void Hero::set_bullet_start()
    {
        bullet_start.x = ul_corner.x + to_float(sprites[POSITION_CENTER]->w) + to_float(HERO_WEAPON_START_SHIFTX);
        bullet_start.y = ul_corner.y + to_float(sprites[to_int(hero_position)]->h) / 2 - 3;
    }

void Hero::Reset_hero_position()
{
    hero_position = Position::center;
    set_bullet_start();
}

void Hero::recompute_intersect_vect()
{
    intersect_vect[0]->x = ul_corner.x + to_float(sprites[CENTER_SPRITE]->x);
    intersect_vect[0]->y = ul_corner.y + FIRST_INTERSECTION_RECT_SHIFTY;

    intersect_vect[1]->x = ul_corner.x + SECOND_INTERSECTION_RECT_SHIFTX;
    intersect_vect[1]->y = ul_corner.y;
}

//Отрисовка прямоугольников коллизии
void Hero::Draw_intersects(const sdl_t& sdl)
{
    for (auto rect : intersect_vect)
    {
        SDL_SetRenderDrawColor(sdl.gRenderer, 0xFF, 0x0, 0x0, 0xFF);
        SDL_RenderDrawRectF(sdl.gRenderer, rect);
    }
}

void Hero::Move(const float speed)
{
    switch (hero_direction)
    {
        case Direction::right:
        {
            if (is_crossing_right(ul_corner.x + sprites[POSITION_CENTER]->w)) return;
            hero_position = Position::center;
            ul_corner.x += speed;
            break;
        }
        case Direction::left:
        {
            if (is_crossing_left(ul_corner.x)) return;
            hero_position = Position::center;
            ul_corner.x -= speed;
            break;
        }
        case Direction::up:
        {
            if (is_crossing_up(ul_corner.y)) return;
            hero_position = Position::up;
            ul_corner.y -= speed;
            break;
        }
        case Direction::down:
        {
            if (is_crossing_down(ul_corner.y + sprites[POSITION_CENTER]->h)) return;
            hero_position = Position::down;
            ul_corner.y += speed;
            break;
        }
        default: {}
    }
        set_bullet_start();
        recompute_intersect_vect();
}

    void Hero::Draw()
    {
        all_textures[to_int(hero_position)]->Render(ul_corner, 
                                sprites[to_int(hero_position)]);
    }

    bool Hero::Is_created()
    {
        return all_textures_are_created;
    }

    void Hero::Walk_stright(bool& is_walk_stright)
    {
        hero_direction = Direction::right;
        Move(HERO_WALKING_STRIGHT_SPEED);
        set_bullet_start();
        recompute_intersect_vect();
        if (hero_in_work_position) stop_walk_stright;
    }



}



