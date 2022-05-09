#include "video_engine.hpp"

#define BLACK_SCREEN 0x0, 0x0, 0x0, 0xFF

#ifdef FLEET_BY_LIST
    #define list_begin fleet.list->begin()
    #define list_end   fleet.list->end()
#endif



void CLS(const sdl_t& sdl)
{
    SDL_SetRenderDrawColor(sdl.gRenderer, BLACK_SCREEN);
    SDL_RenderClear(sdl.gRenderer);
}

bool Init_sdl(sdl_t& sdl, const char* title)
{
    sdl.gWindow =   nullptr;
    sdl.gRenderer = nullptr;
    sdl.sdl_ok = true;
    sdl.history = HISTORY::intro;
    sdl.game_pause = false;
    sdl.game_quit = false;

    if(SDL_Init( SDL_INIT_VIDEO ) < 0)
    {
        std::cout << "Невозможно инициализировать SDL. Ошибка " << SDL_GetError() << '\n';
        return false;
    }

    if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        std::cout << "Не подключена опция linear texture filtering." ;
        return false;
    }

    sdl.gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, S_W, S_H, SDL_WINDOW_SHOWN);
    if(!sdl.gWindow)
    {
        std::cout << "Невозможно инициализировать окно window, ошибка " << SDL_GetError() << '\n';
        return false;
    }
    sdl.gRenderer = SDL_CreateRenderer(sdl.gWindow, -1, SDL_RENDERER_SOFTWARE /*SDL_RENDERER_ACCELERATED*/);
    if(!sdl.gRenderer)
    {
        std::cout << "Невозможно инициализировать параметр Renderer, ошибка " << SDL_GetError() << '\n';
        return false;
    }

    int imgFlags = IMG_INIT_JPG;
    if(!(IMG_Init(imgFlags) & imgFlags))
    {
        std::cout << "Невозможно инициализировать SDL_image, ошибка " << IMG_GetError() << '\n';
        return false;
    }

    if( TTF_Init() == -1)
    {
        std::cout << "Невозможно инициализировать SDL_ttf, ошибка." << TTF_GetError() << '\n';
        return false;
    }
    return true;


}

void Close_sdl(sdl_t& sdl)
{
    SDL_DestroyRenderer(sdl.gRenderer);
    SDL_DestroyWindow(sdl.gWindow);
    sdl.gRenderer= nullptr;
    sdl.gWindow= nullptr;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

#ifdef DRAW_INTERSECTS
//Отрисовка героя с прямоугольниками коллизии
void Draw_heros(sdl_t& sdl, hero_t& hero)
{
    hero.hero->Draw();
    hero.hero->Draw_intersects(sdl);
}
#else
//Отрисовка героя без прямоугольников коллизии
void Draw_heros(hero_t& hero)
{
    hero.hero->Draw();
}
#endif

//Отрисовка заднего рисунка и звезд
void Draw_backs(backs_t& backs)
{
    auto ptr_f = &backs.fast[0];
    auto ptr_s = &backs.slow[0];

    backs.fon->Draw();
    
    for (;;ptr_f++)
    {
        if (ptr_f == &backs.fast[FAST_STAR_COUNT]) break;
        ptr_f->Draw();
    }
    for (;;ptr_s++)
    {
        if (ptr_s == &backs.slow[SLOW_STAR_COUNT]) break;
        ptr_s->Draw();
    }
}


#ifdef DRAW_INTERSECTS
    //Отрисовка флота вражеских кораблей
    void Show_fleet(sdl_t& sdl, fleet_t& fleet)
    {
        #ifdef FLEET_BY_LIST
        //std::list<Alien_stright_one*>::iterator it;
        fleet_iterator it;
        for (it = list_begin; it != list_end; it++)
        {
            if ( (*it)->Ship_is_visible())
            {
                (*it)->Draw_intersects(sdl);
                (*it)->Draw();
            }
        }
        #else
        auto ptr = &fleet.stright_fleet_arr[0];
        for (;;ptr++)
        {
            if (ptr == &fleet.stright_fleet_arr[STRIGHT_FLEET_COUNT]) break;
            if (ptr->Ship_is_visible())
            {
                ptr->Draw_intersects(sdl);
                ptr->Draw();
            }
        } 
        #endif
    }
#else 
    //Отрисовка флота вражеских кораблей
    void Show_fleet(fleet_t& fleet)
    {
        #ifdef FLEET_BY_LIST
            for (fleet_iterator it = list_begin; it != list_end; it++)
            {
                //if ( (*it)->Ship_is_visible()) (*it)->Draw();
                (*it)->Draw();
            }
        #else
            auto ptr = &fleet.stright_fleet_arr[0];
            for (;;ptr++)
            {
                if (ptr == &fleet.stright_fleet_arr[STRIGHT_FLEET_COUNT]) break;
                if (ptr->Ship_is_visible()) ptr->Draw();
            }
        #endif
    }
#endif

bool Init_pause(sdl_t& sdl, pause_t& pause)
{
    pause.params.color = pause_color;
    pause.params.text = "PAUSE";
    pause.params.text_size = PAUSE_SIZE;

    pause.pause_text = new Text_texture {sdl.gRenderer, pause.params};
    float texture_pause_half_w = pause.pause_text->Get_texture_w() / 2;
    float texture_pause_half_h = pause.pause_text->Get_texture_h() / 2;
    pause.ul_corner = { (S_W/2 - texture_pause_half_w), (S_H/2 - texture_pause_half_h)};


    pause.sub_params.color = pause_sub_color;
    pause.sub_params.text  = "Press Esc to continue, Q to exit";
    pause.sub_params.text_size = PAUSE_SUB_SIZE;
    pause.pause_sub_text = new Text_texture {sdl.gRenderer, pause.sub_params};
    float texture_pause_sub_half_w = pause.pause_sub_text->Get_texture_w() / 2;
    pause.ul_corner_sub = { (S_W/2 - texture_pause_sub_half_w), (BORDER_DOWN - 50)};
    return ( (pause.pause_text->Texture_is_created()) && (pause.pause_sub_text->Texture_is_created()) );
}

void Close_pause(pause_t& pause)
{
    if (pause.pause_text)
    {
        delete pause.pause_text;
        pause.pause_text = nullptr;
    }
    if (pause.pause_sub_text)
    {
        delete pause.pause_sub_text;
        pause.pause_sub_text = nullptr;
    }
}

void Draw_border(sdl_t& sdl, border_t& b)
{
    b.Draw_border(sdl);
}
