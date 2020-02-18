#pragma once
#include <SDL2/SDL.h>

#include "utills.h"

class render_object_t
{
public:
    render_object_t(config_pointer config)
    {
        config_ = config;
    }
    virtual void draw(SDL_Renderer *renderer);
    cords_t cordinates_;
    // size_t size_;
    config_pointer config_;
    //SOME IMG OR COLOR ???????????
};