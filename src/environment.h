#pragma once

#include "render_object.h"
#include "utils.h"

class environment_t : public render_object_t
{

public:
    void draw_f(SDL_Renderer *renderer);
    environment_t(std::shared_ptr<config_t> config, cords_t coordinates) : render_object_t(config, coordinates){};
    ENV state_ = ENV::SAND;
};