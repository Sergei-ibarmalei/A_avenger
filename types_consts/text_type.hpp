#ifndef TEXT_TYPE_HPP
#define TEXT_TYPE_HPP

#include "../classes/text_texture.hpp"

using namespace classes;

namespace text_type
{
    typedef struct 
    {
        text_t params;
        text_t sub_params;
        Text_texture* pause_text     = nullptr;
        Text_texture* pause_sub_text = nullptr;
        plot_t ul_corner;
        plot_t ul_corner_sub;

        void Draw_pause()
        {
            pause_text->Render(ul_corner);
            pause_sub_text->Render(ul_corner_sub);
        }

        
    } pause_t;
}

#endif