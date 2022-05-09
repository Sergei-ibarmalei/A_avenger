#include "engine.hpp"

#ifdef FLEET_BY_LIST
    #define fleet_list_begin fleet.list->begin()
    #define fleet_list_end   fleet.list->end()
#endif
#define store_list_begin laser_store_list->begin()
#define store_list_end   laser_store_list->end()
#define hero_laser_store_empty store.hero_laser_store->empty()
#define list_begin list->begin()
#define list_end   list->end()
#ifdef FLEET_BY_LIST
bool check_rect_list(SDL_FRect* rect, fleet_list* list);
#else
bool check_rect_fleetarr(SDL_FRect* rect, Alien_stright_one* fleet_arr);
#endif


#define LEFTA   a->x
#define RIGHTA  a->x + a->w
#define TOPA    a->y
#define BOTTOMA a->y + a->h

#define LEFTB   b->x
#define RIGHTB  b->x + b->w
#define TOPB    b->y
#define BOTTOMB b->y + b->h

#define alien_in_array_is_invisible !fleet_arr[i].Ship_is_visible()
#define alien_ship_is_outscreen     alien_ship->Alien_is_outofscreen()
#define alien_is_not_created      (!alien || !alien->Is_created())
#define laser_store_init_ok  (store.hero_laser_store != nullptr && store.aliens_laser_store != nullptr)


template<class T, class L>
void delete_object_from_list(T& it, L* list)
{
    delete (*it);
    (*it) = nullptr;
    list->erase(it);
}

bool check_collision(SDL_FRect* a, SDL_FRect* b);
bool check_rect_vector_rect(SDL_FRect* rect, frect_vect& vect);
void move_hero_lasers(Laser_store_list* laser_store_list);
void Check_keys(sdl_t& sdl, hero_t& hero, weapon_store_t& store);
bool push_alien(sdl_t& sdl, fleet_t& fleet, int count = 0);


#ifdef DRAW_INTERSECTS
    void draw_hero_lasers(sdl_t& sdl, Laser_store_list* laser_store_list);
#else
    void draw_hero_lasers(Laser_store_list* laser_store_list);
#endif

//Инициализация героя
bool Init_hero(sdl_t& sdl, hero_t& hero)
{
    hero.hero = new Hero {sdl.gRenderer};
    return hero.hero->Is_created();
}

//Очистка героя
void Close_hero(hero_t& hero)
{
    if (hero.hero)
    {
        delete hero.hero;
        hero.hero = nullptr;
    }
}

//Проверка нажатых клавиш
void Check_keys(sdl_t& sdl, hero_t& hero, weapon_store_t& weapon)
{
    //if ( (sdl.game_pause) || (hero.walk_stright)) return;

    switch (sdl.e.key.keysym.sym)
    {
        case SDLK_UP:
        {
            if ( (sdl.game_pause) || (hero.walk_stright)) return;
            hero.hero->Goes_up();
            hero.hero->Move(HERO_SPEED); 
            break;
        }
        case SDLK_DOWN:
        {
            if ( (sdl.game_pause) || (hero.walk_stright)) return;
            hero.hero->Goes_down();
            hero.hero->Move(HERO_SPEED);
            break;
        }
        case SDLK_RIGHT:
        {
            if ( (sdl.game_pause) || (hero.walk_stright)) return;
            hero.hero->Goes_right();
            hero.hero->Move(HERO_SPEED);
            break;
        }
        case SDLK_LEFT:
        {
            if ( (sdl.game_pause) || (hero.walk_stright)) return;
            hero.hero->Goes_left();
            hero.hero->Move(HERO_SPEED);
            break;
        }
        case SDLK_SPACE:
        {
            if ( (sdl.game_pause) || (hero.walk_stright)) return;
            weapon.hero_laser_store->push_back(new Laser {sdl.gRenderer, 
                                                Laser_kind::red, hero.hero->Bullet_start(), DIRECTION::right});
            break;
        }
        case SDLK_ESCAPE:
        {
            if (sdl.game_pause == false) sdl.game_pause = true;
            else sdl.game_pause = false;
            break;
        }
        default: {}
    }
}


//Инициализация заднего фона - картинки и звезд
bool Init_backs(sdl_t& sdl, backs_t& backs)
{
    bool init_ok = true;

    backs.fast = new Star[FAST_STAR_COUNT];
    backs.slow = new Star[SLOW_STAR_COUNT];
    auto ptr_f = &backs.fast[0];
    auto ptr_s = &backs.slow[0];
    for (;;ptr_f++)
    {
        if (ptr_f == &backs.fast[FAST_STAR_COUNT]) break;

        ptr_f->Make_star(sdl.gRenderer);
        if (!ptr_f->Is_init())
        {
            init_ok = false; 
            return init_ok;
        }
    }
    for (;;ptr_s++)
    {
        if (ptr_s == &backs.slow[SLOW_STAR_COUNT]) break;
        ptr_s->Make_star(sdl.gRenderer);
        if (!ptr_s->Is_init())
        {
            init_ok = false;
            return init_ok;
        }
    }

    backs.fon = new Back_fon{sdl.gRenderer, sdl.history};
    if (!backs.fon->Is_init()) init_ok = false;
    return init_ok;
}

//Очистка заднего фона
void Close_backs(backs_t& backs)
{
    if (backs.fast)
    {
        delete[] backs.fast;
        backs.fast = nullptr;
    }
    if (backs.slow)
    {
        delete[] backs.slow;
        backs.slow = nullptr;
    }
    if (backs.fon)
    {
        delete backs.fon;
        backs.fon = nullptr;
    }
}

//Движение звезд на заднем фоне
void Move_backs(backs_t& backs)
{
    auto fast_star = &backs.fast[0];
    auto slow_star = &backs.slow[0];
    for (;;fast_star++)
    {
        if (fast_star == &backs.fast[FAST_STAR_COUNT]) break;
        fast_star->Move(FAST_STAR_SPEED);
    }
    for (;;slow_star++)
    {
        if (slow_star == &backs.slow[SLOW_STAR_COUNT]) break;
        slow_star->Move(SLOW_STAR_SPEED);
    }
}

//Инициализация флота вражеских кораблей
bool Init_fleet(sdl_t& sdl, fleet_t& fleet)
{
    bool init_ok = true;

    #ifdef FLEET_BY_LIST
    fleet.list = new fleet_list;

        #ifdef ONE_ALIEN_IN_FLEET
            return push_alien(sdl, fleet);
        #else
            for (size_t i = 0; i < STRIGHT_FLEET_COUNT; i++)
            {
                if (!push_alien(sdl,fleet, i)) 
                {
                    std::cout << "return false.\n"; return false;
                }
            }
        #endif
        return init_ok;

    #else
        fleet.stright_fleet_arr = new Alien_stright_one[STRIGHT_FLEET_COUNT];
        if (!fleet.stright_fleet_arr) return false;
        auto alien_ship = &fleet.stright_fleet_arr[0];
        for (;;alien_ship++)
        {
            if (alien_ship == &fleet.stright_fleet_arr[STRIGHT_FLEET_COUNT]) break;
            float speed = get_alien_speed();
            alien_ship->Set_speed(speed);
            alien_ship->Make_alien(sdl.gRenderer);
        }
        return init_ok;
    #endif
}

bool push_alien(sdl_t& sdl, fleet_t& fleet, int count)
{
    bool init_ok = true;
    plot_t start_point;
    unsigned alien_step_space = 250;
    Alien_stright_one* alien = new Alien_stright_one {};
    alien->Make_alien(sdl.gRenderer);
    if (alien_is_not_created)
    {
        return false;
    }
    start_point.x = to_float(S_W + 1) + to_float(alien_step_space * count);
    start_point.y = getRandom(BORDER_UP + 100.0f, BORDER_DOWN - 150.0f);
    alien->UL_corner() = start_point;
    float speed = get_alien_speed();
    alien->Set_speed(speed);
    fleet.list->push_back(alien);
    return init_ok;
}

//Очистка флота вражеских кораблей
void Close_fleet(fleet_t& fleet)
{
    #ifdef FLEET_BY_LIST
        if (fleet.list)
        {
            fleet_iterator it;
            fleet_iterator for_delete;
            for (it = fleet_list_begin; it != fleet_list_end;)
            {
                for_delete = it;
                it++;
                delete (*for_delete);
                (*for_delete) = nullptr;
            }
            delete fleet.list;
            fleet.list = nullptr;
        }
    #else
        if (fleet.stright_fleet_arr)
        {
            delete[] fleet.stright_fleet_arr;
            fleet.stright_fleet_arr = nullptr;
        }

    #endif
}

//Движение флота вражеских кораблей
void Move_fleet(fleet_t& fleet)
{
    #ifdef FLEET_BY_LIST
        for (fleet_iterator it = fleet_list_begin; it != fleet_list_end; it++)
        {
            (*it)->Move((*it)->Alien_speed());
            if ( (*it)->Alien_is_outofscreen())
            {
                (*it)->Ship_is_visible() = false;
                (*it)->Make_new_ulcorner();
                (*it)->Set_speed(get_alien_speed());
            }
            else (*it)->Ship_is_visible() = true;
        }
    #else
        auto alien_ship = &fleet.stright_fleet_arr[0];
        for (;;alien_ship++)
        {
            if (alien_ship == &fleet.stright_fleet_arr[STRIGHT_FLEET_COUNT]) break;
            //if (alien_ship_is_invisible) continue;
            alien_ship->Move(alien_ship->Alien_speed());
            if (alien_ship_is_outscreen)
            {
                alien_ship->Make_new_ulcorner();
                alien_ship->Set_speed(get_alien_speed());
            }
        }
    #endif

}

//Проверка столкновения героя и флота алиенов
void Check_collisions(hero_t& hero, fleet_t& fleet)
{
    bool has_collision = false;
    #ifdef FLEET_BY_LIST

        auto vector_ = hero.hero->get_intersect_vect();
        for (auto rect : vector_)
        {
            has_collision = check_rect_list(rect, fleet.list);
            if (has_collision) std::cout << "hero's dead.\n";
        }

    #else //Fleet_by_array
        auto vector_ = hero.hero->get_intersect_vect();
        for (auto rect : vector_)
        {
            has_collision =  check_rect_fleetarr(rect, fleet.stright_fleet_arr);
            if (has_collision) std::cout << "Hero is dead!\n";
            break;
        }
    #endif
    //return has_collision;
}

#ifdef FLEET_BY_LIST
//Проверка на коллизию одного прям. героя и флота врагов
bool check_rect_list(SDL_FRect* rect , fleet_list* list)
{
    fleet_iterator for_delete;

    bool collision = false;

    for (fleet_iterator it = list_begin; it != list_end; it++)
    {

        if (check_rect_vector_rect(rect, (*it)->get_intersect_vect()))
        {
            collision = true;
            for_delete = it;
            it ++;
            //delete_alien_from_fleet(for_delete, l);
            delete_object_from_list(for_delete, list);
            break;
        }
    }
    return collision;
}
#else

//Проверка на коллизию одного прям. героя и флота врагов
bool check_rect_fleetarr(SDL_FRect* rect, Alien_stright_one* fleet_arr)
{
    bool collision = false;
        
    for (size_t i = 0; i < STRIGHT_FLEET_COUNT; i++)
    {
        if (alien_in_array_is_invisible) continue;

        if (check_rect_vector_rect (rect, fleet_arr[i].get_intersect_vect()))
        {
            collision = true;
            fleet_arr[i].Ship_is_visible() = false;
            break;
        }
    }
    return collision;
}
#endif

//Проверка одного прям. героя и вектора прям. одного вражеского корабля
bool check_rect_vector_rect(SDL_FRect* rect, frect_vect& vect)
{
    bool collision = false;
    for (auto alien_intersect_rect : vect)
    {
        if (check_collision(rect, alien_intersect_rect))
        {
            collision = true; break;
        }
    }
    return collision;
}

//Проверка на столкновение двух прямоугольников
bool check_collision(SDL_FRect* a, SDL_FRect* b)
{
    if (BOTTOMA <= TOPB) return false;
    if (TOPA >= BOTTOMB) return false;
    if (RIGHTA <= LEFTB) return false;
    if (LEFTA >= RIGHTB) return false;
    return true;
}

//Инициализация лазеров
bool Init_Laserstore(weapon_store_t& store)
{
    store.hero_laser_store = new Laser_store_list;
    store.aliens_laser_store = new Laser_store_list;
    return ( laser_store_init_ok);
}

//Очистка магазина лазеров
void Close_Laserstore(weapon_store_t& store)
{
    if (store.hero_laser_store)
    {
        delete store.hero_laser_store;
        store.hero_laser_store = nullptr;
    }
    if (store.aliens_laser_store)
    {
        delete store.aliens_laser_store;
        store.aliens_laser_store = nullptr;
    }
}

//Движение лазеров
void Move_lasers(weapon_store_t& store)
{
    
    if (hero_laser_store_empty) return;
    move_hero_lasers(store.hero_laser_store);
}

#ifdef DRAW_INTERSECTS
    //Отрисовка лазеров
    void Draw_lasers(sdl_t& sdl, weapon_store_t& store)
    {
        draw_hero_lasers(sdl, store.hero_laser_store);
    }
#else
    //Отрисовка лазеров
    void Draw_lasers(weapon_store_t& store)
    {
        if (hero_laser_store_empty) return;

        draw_hero_lasers(store.hero_laser_store);
    }
#endif

//Движение лазера героя
void move_hero_lasers(Laser_store_list* laser_store_list)
{
    laser_iterator for_delete;

    for (laser_iterator it = store_list_begin; it != store_list_end; it++)
    {
        (*it)->Move();
        //Если лазер вышел за пределы экрана, то удаляем его из списка
        if (!(*it)->Is_visible())
        {
            for_delete = it;
            it++;
            delete_object_from_list(for_delete, laser_store_list);
        }
    }

}

#ifdef DRAW_INTERSECTS
    //Рисуем лазеры в цикле
    void draw_hero_lasers(sdl_t& sdl, Laser_store_list* laser_store_list)
    {
        for (laser_iterator it = store_list_begin; it != store_list_end; it++)
        {
            if (!(*it)->Is_visible()) continue;
            (*it)->Draw();
            (*it)->Draw_intersect(sdl);
        }
    }
#else
    //Рисуем лазеры в цикле
    void draw_hero_lasers(Laser_store_list* laser_store_list)
    {
        for (laser_iterator it = store_list_begin; it != store_list_end; it++)
        {
            if (!(*it)->Is_visible()) continue;
            (*it)->Draw();
        }
    }
#endif

//Проверка столкновений лазера и врагов
void Laser_collisions_aliens(weapon_store_t store, fleet_t& alien_fleet)
{
    laser_iterator for_delete;

    #ifdef FLEET_BY_LIST
        if (store.hero_laser_store->empty()) return;
        for (laser_iterator it_ = store.hero_laser_store->begin(); it_ != store.hero_laser_store->end(); it_++)
        {
            //Проверяем на коллизию прямоугольник и список
            if ( check_rect_list( (*it_)->Laser_intersect_rect(), alien_fleet.list))
            //Если лазер попал в какой либо корабль  из массива вражеских кораблей
            //то удаляем лазер из списка лазеров
            {
                for_delete = it_;
                it_ ++;
                delete_object_from_list(for_delete,store.hero_laser_store);
            }
        }
    #else
        if (store.hero_laser_store->empty()) return;
        for (laser_iterator it_ = store.hero_laser_store->begin(); it_ != store.hero_laser_store->end(); it_++)
        {
            //Проверяем на коллизию прямоугольник и массив
            if ( check_rect_fleetarr( (*it_)->Laser_intersect_rect(), alien_fleet.stright_fleet_arr))
            //Если лазер попал в какой либо корабль  из массива вражеских кораблей
            //то удаляем лазер из списка лазеров
            {

                for_delete = it_;
                it_ ++;
                delete_object_from_list(for_delete, store.hero_laser_store);
            }
        }
    #endif
}

//Проверка на нажатие клавиш
void Player_action(sdl_t& sdl, hero_t& hero, weapon_store_t& hero_laser_store)
{
        while (SDL_PollEvent(&sdl.e))
        {
            if (sdl.e.type == SDL_QUIT) sdl.game_quit = true;


            else if(sdl.e.type == SDL_KEYDOWN)
            {
                Check_keys(sdl, hero, hero_laser_store);
            }
            else if (sdl.e.type == SDL_KEYUP)
            {
                hero.hero->Reset_hero_position();
            }
        }
}



