#pragma once
#include <SDL2/SDL.h>

#include "utills.h"

class render_object_t
{
public:
    virtual void draw(SDL_Renderer *renderer);
    cords_t cordinates_;
    size_t size_;
    std::shared_ptr<config_t> config_;
    //SOME IMG OR COLOR ???????????
};