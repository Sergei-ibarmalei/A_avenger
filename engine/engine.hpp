#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "../types_consts/hero_type.hpp"
#include "../types_consts/border_consts.hpp"
#include "../types_consts/backs_type.hpp"
#include "../types_consts/fleet_type.hpp"
#include "../types_consts/weapon_store_type.hpp"
#include "../engine/myrand.hpp"
#include "../classes/alien_stright_one.hpp"



using namespace border_consts;
using namespace backs_type;
using namespace fleet_type;
using namespace classes;
using namespace myrand;
using namespace weapon_store;

bool Init_hero(sdl_t& sdl, hero_t& hero);
void Close_hero(hero_t& hero);

bool Init_backs(sdl_t& sdl, backs_t& backs);
void Close_backs(backs_t& backs);
void Move_backs(backs_t& backs);
bool Init_fleet(sdl_t& sdl, fleet_t& fleet);
void Close_fleet(fleet_t& fleet);
bool Init_Laserstore(weapon_store_t& store);
void Close_Laserstore(weapon_store_t& store);
void Move_fleet(fleet_t& fleet);
void Move_lasers(weapon_store_t& store);
#ifdef DRAW_INTERSECTS
    void Draw_lasers(sdl_t& sdl, weapon_store_t& store);
#else
    void Draw_lasers(weapon_store_t& store);
#endif
void Check_collisions(hero_t& hero, fleet_t& fleet);
void Laser_collisions_aliens(weapon_store_t store, fleet_t& alien_fleet);
void Player_action(sdl_t& sdl, hero_t& hero, weapon_store_t& hero_laser_store);




#endif