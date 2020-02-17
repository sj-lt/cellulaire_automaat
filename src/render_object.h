#pragma once
#include <SDL2/SDL.h>

#include "utills.h"

class render_object_t
{
public:
    void draw(SDL_Renderer *renderer);
    cords_t cordinates_;
    size_t size_;
    //SOME IMG OR COLOR ???????????
};

