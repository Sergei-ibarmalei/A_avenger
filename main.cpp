#include "types_consts/sdl_type.hpp"
#include "types_consts/test.hpp"
#include "video_engine/video_engine.hpp"
#include "engine/engine.hpp"




#define WALK_STRIGHT hero.walk_stright
#define GAME_PAUSE   sdl.game_pause

int main(int argc, char* argv[])
{
    srand(time(NULL));

    sdl_t sdl;
    hero_t hero;
    backs_t backs;
    fleet_t stright_fleet;
    weapon_store_t Laser_store;
    pause_t pause; 
    border_t border;

    if (!Init_sdl(sdl, "A_Avenger")) return 1;
    if (!Init_hero(sdl, hero)) return 1;
    if (!Init_backs(sdl, backs)) return 1;
    if (!Init_fleet(sdl, stright_fleet)) return 1;
    if (!Init_Laserstore(Laser_store)) return 1;
    if (!Init_pause(sdl, pause)) return 1;




    while (!sdl.game_quit)
    {
        Player_action(sdl, hero, Laser_store);
        CLS(sdl);
        Draw_backs(backs);
        if (WALK_STRIGHT)
        {
            if (GAME_PAUSE)
            {
            #ifdef DRAW_INTERSECTS
                Draw_heros(sdl,hero);
            #else
                Draw_heros(hero);
            #endif
                Move_backs(backs);
                pause.Draw_pause();
                Draw_border(sdl, border);
                SDL_RenderPresent(sdl.gRenderer);
                continue;
            }
            hero.hero->Walk_stright(hero.walk_stright);
            #ifdef DRAW_INTERSECTS
                Draw_heros(sdl, hero);
                Move_backs(backs);
            #else
                Draw_heros(hero);
                Move_backs(backs);
            #endif
            Draw_border(sdl, border);
            SDL_RenderPresent(sdl.gRenderer);
            continue;
        }
        if (GAME_PAUSE)
        {
            #ifdef DRAW_INTERSECTS
                Draw_heros(sdl, hero);
                Show_fleet(sdl, stright_fleet);
                Draw_lasers(sdl, hero_laser_store);
            #else
                Draw_heros(hero);
                Show_fleet(stright_fleet);
                Draw_lasers(Laser_store);
            #endif
            Move_backs(backs);
            pause.Draw_pause();
            Draw_border(sdl, border);
            SDL_RenderPresent(sdl.gRenderer);
            continue;
        }
        #ifdef DRAW_INTERSECTS
            Draw_heros(sdl, hero);
            Show_fleet(sdl, stright_fleet);
            Draw_lasers(sdl, hero_laser_store);
        
        #else
            Draw_heros(hero);
            Show_fleet(stright_fleet);
            Draw_lasers(Laser_store);
        #endif

        Move_backs(backs);
        Move_fleet(stright_fleet);
        Move_lasers(Laser_store);
        Check_collisions(hero, stright_fleet);
        Laser_collisions_aliens(Laser_store,stright_fleet);
        Draw_border(sdl, border);
        SDL_RenderPresent(sdl.gRenderer);
    }

    Close_sdl(sdl);
    Close_hero(hero);
    Close_fleet(stright_fleet);
    Close_backs(backs);
    Close_Laserstore(Laser_store);
    Close_pause(pause);


    return 0;
}


