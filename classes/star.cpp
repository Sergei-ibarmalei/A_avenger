#include "star.hpp"
namespace classes
{
    Star::Star()
    {
        ul_corner.x = getRandom(0, S_W);
        ul_corner.y = getRandom(BORDER_UP + 1, S_H);
    }

    Star::~Star()
    {
        if (texture)
        {
            delete texture;
            texture = nullptr;
        }
}

    void Star::Make_star(SDL_Renderer* r)
    {
        texture = new Image_texture {r, STAR_FILE_NAME};
    }

    void Star::Draw()
    {
        texture->Render(ul_corner);
    }

    void Star::Move(const float speed)
    {
        ul_corner.x -= speed;
        if (is_crossing_left(ul_corner.x + speed))
        {
            ul_corner.x = getRandom(S_W, S_W + 300);
            ul_corner.y = getRandom(static_cast<int>(BORDER_UP), S_H);
        }
    }
}



