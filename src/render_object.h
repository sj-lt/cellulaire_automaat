#pragma once
#include <SDL2/SDL.h>

#include "utils.h"

class render_object_t
{
public:
    render_object_t(std::shared_ptr<config_t> config, cords_t coordinates);

    virtual void draw_f(SDL_Renderer *renderer){};
    cords_t coordinates_;
    // size_t size_;
    std::shared_ptr<config_t> config_;
    //SOME IMG OR COLOR ???????????
};